#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include "utils/Destination.h"
#include "utils/Client.h"
#include "utils/Disposer.h"

Destination upper_base(5, 60);
Destination middle_base(10, 60);
Destination lower_base(15, 60);
Disposer dispo(10, 45);

std::vector<Client *> clients;
std::vector<Destination> destinations{upper_base, middle_base, lower_base};

std::mutex clients_mutex;
std::condition_variable cond_var;

bool end_condition = false;
int disposer_destination = 0;

void manage_clients(bool &close) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr_sleep(1, 3);

    auto next_generation_time = std::chrono::steady_clock::now();
    auto next_deletion_time = std::chrono::steady_clock::now();
    auto deletion_interval = std::chrono::seconds(2);

    while (!close) {
        auto current_time = std::chrono::steady_clock::now();
        if (current_time >= next_generation_time) {
            auto *new_client = new Client(10, 10, -1, disposer_destination, dispo, destinations, clients_mutex, cond_var, clients);
            {
                std::lock_guard<std::mutex> lock(clients_mutex);
                clients.push_back(new_client);

            }

            next_generation_time = current_time + std::chrono::seconds(distr_sleep(gen));
        }

        if (current_time >= next_deletion_time) {
            std::lock_guard<std::mutex> lock(clients_mutex);
            for (auto it = clients.begin(); it != clients.end();) {
                Client *client = *it;
                if (client->is_to_erased()) {
                    client->client_thread.join();
                    it = clients.erase(it);
                    delete client;
                } else {
                    ++it;
                }
            }

            next_deletion_time = current_time + deletion_interval;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void disposer(bool &close) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr_client;

    while (!close) {
        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            if (disposer_destination < 2) {
                disposer_destination++;
            } else {
                disposer_destination = 0; // reset disposer_destination to 0
            }
            cond_var.notify_one();
            // Check if any clients are waiting
//            std::vector<Client*> waiting_clients;
//            for (auto &client : clients) {
//                if (client->get_destination() == -1 && client->get_x() == dispo.get_x() - 1) {
//                    waiting_clients.push_back(client);
//                }
//            }
//
//            // Notify one random client from the waiting clients if the path is free
//            if (!waiting_clients.empty()) {
//                distr_client = std::uniform_int_distribution<>(0, waiting_clients.size() - 1);
//                Client* chosen_client = waiting_clients[distr_client(gen)];
//
//                if (!Client::is_occupied(clients, disposer_destination)) {
////                    chosen_client->set_destination(disposer_destination);
//                    cond_var.notify_all();
//                }
//            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}


void print_disposer(int _disposer_destination) {
    switch (_disposer_destination) {
        case 0:
            mvaddch(dispo.get_y(), dispo.get_x(), ACS_UARROW);
            break;
        case 1:
            mvaddch(dispo.get_y(), dispo.get_x(), ACS_RARROW);
            break;
        case 2:
            mvaddch(dispo.get_y(), dispo.get_x(), ACS_DARROW);
            break;
    }
}

void display_all() {
    erase();
    upper_base.draw_borders();
    middle_base.draw_borders();
    lower_base.draw_borders();

    for (auto &client : clients) {
        mvprintw(client->get_y(), client->get_x(), "%c", client->get_sign()); // Print existing positions of clients
    }

    print_disposer(disposer_destination); // Print the disposer arrow based on current disposer_destination
    refresh();
}

int main() {
    initscr(); // Initialize ncurses
    nodelay(stdscr, TRUE);
    curs_set(0);
    noecho();

    std::thread generate_clients_thread(manage_clients, std::ref(end_condition)); // Clients generation thread
    std::thread disposer_thread(disposer, std::ref(end_condition)); // The disposer thread

    while (!end_condition) {

        display_all(); // Display everything

        int c = getch();
        if (c == ' ') {
            end_condition = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    endwin(); // End ncurses mode
    std::cout << "*** CLOSING ALL OF THE THREADS ***\n";


    generate_clients_thread.join();
    std::cout << "** Management of clients thread stopped **\n";

    disposer_thread.join();
    std::cout << "** The disposer thread stopped **\n";

    for (auto it = clients.begin(); it != clients.end();) {
        Client *client = *it;
        client->client_thread.join();
        it = clients.erase(it);
        delete client;
    }

    std::cout << "Finished\n";

    return 0;
}
