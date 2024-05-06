#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include "utils/Destination.h"
#include "utils/Client.h"
#include "utils/Disposer.h"


Destination upper_base(5, 60);
Destination middle_base(10, 60);
Destination lower_base(15, 60);
Disposer dispo(10,45);


std::vector<Client*> clients;
std::vector<Destination> destinations{upper_base, middle_base, lower_base};

volatile bool end_condition = false;
int disposer_destination = 0;


void generate_clients(volatile bool &close) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr_sleep(3, 7);

    while (!close) {
        std::this_thread::sleep_for(std::chrono::seconds(distr_sleep(gen)));

        auto *new_client = new Client(10, 10, -1, disposer_destination, dispo, destinations);
        {
//            std::lock_guard<std::mutex> lock(clients_mutex);
            clients.push_back(new_client);
//            std::cout << "New client created at: " << new_client->get_x() << ", " << new_client->get_y() << std::endl;
        }
    }

}


void disposer(volatile bool &close) {
    while (!close) {
        if (disposer_destination < 2) {
            disposer_destination++;
        } else {
            disposer_destination = 0; // reset disposer_destination to 0
        }
        // Sleep for 3 seconds
        std::this_thread::sleep_for(std::chrono::seconds(3));
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
        clear();
        // Move existing clients
        upper_base.draw_borders();
        middle_base.draw_borders();
        lower_base.draw_borders();
        // Print the disposer arrow based on current disposer_destination

        for (auto& client : clients) {
        mvprintw((*client).get_y(), (*client).get_x(), "%c", (*client).get_sign());
        }
        print_disposer(disposer_destination);

        // Refresh the screen
        refresh();

}

int main() {
    initscr(); // Initialize ncurses
//    curs_set(0); // Hide the cursor
    nodelay(stdscr, TRUE); // Set non-blocking input

    // Start the client generation thread
    std::thread generate_clients_thread(generate_clients, std::ref(end_condition));
    // Start the disposer thread
    std::thread disposer_thread(disposer, std::ref(end_condition));

    while (!end_condition) {

//        Update client movements
        for (auto& client : clients) {
            mvprintw((*client).get_y(), (*client).get_x(), "%c", (*client).get_sign());
        }



        // Display everything
        display_all();
        int c = getch();
        if (c == ' ') {
            end_condition = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    endwin(); // End ncurses mode
    // Stop the client generation thread

    generate_clients_thread.join();

    // Wait for the disposer thread to finish
    disposer_thread.join();

    std::cout << "finished\n";


    return 0;
}

