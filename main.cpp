#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include "utils/Destination.h"
#include "utils/Client.h"
#include "utils/Disposer.h"

int DIRECTOR_Y = 10;
int DIRECTOR_X = 45;

Destination upper_base(5, 60);
Destination middle_base(10, 60);
Destination lower_base(15, 60);
Disposer dispo(10,45);
//  std::mutex vectorMutex;

std::vector<Client> clients;
std::vector<Destination> destinations{upper_base, middle_base, lower_base};
bool end_condition = false;
bool generate_c = true;
int disposer_destination = 0;

void generate_clients() {
    while(generate_c) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr_sleep(6,10);

//        std::lock_guard<std::mutex> lock(vectorMutex);
        Client newClient(10, 10, -1);
        clients.push_back(newClient);

        std::this_thread::sleep_for(std::chrono::seconds(1 * distr_sleep(gen)));
    }
}

void disposer(bool close) {
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
            mvaddch(DIRECTOR_Y, DIRECTOR_X, ACS_UARROW);
            break;
        case 1:
            mvaddch(DIRECTOR_Y, DIRECTOR_X, ACS_RARROW);
            break;
        case 2:
            mvaddch(DIRECTOR_Y, DIRECTOR_X, ACS_DARROW);
            break;
    }
}

void display_all() {
    clear();

    while (!end_condition) {
        clear();

        // Move existing clients
        for(auto &client: clients) {
            client.move(disposer_destination, dispo, destinations);
            mvprintw(client.get_y(), client.get_x(), "%c", client.get_sign());
        }

        upper_base.draw_borders();
        middle_base.draw_borders();
        lower_base.draw_borders();

        // Print the disposer arrow based on current disposer_destination
        print_disposer(disposer_destination);

        // Refresh the screen
        refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        // Check if the disposer thread has finished
        if (end_condition)
            break;
    }
}

int main() {
    initscr();

    // Start the client generation thread
    std::thread generate_clients_thread(generate_clients);

    // Start the disposer thread
    std::thread disposer_thread(disposer, std::ref(end_condition));

    // Run the main display loop
    display_all();

    int ch = getch();
    if(ch == ' ') {
        end_condition = false;
        generate_c = false;
        generate_clients_thread.join();
        disposer_thread.join();
    }
//    // Stop the client generation thread
//    generate_c = false;
//    generate_clients_thread.join();
//
//    // Wait for the disposer thread to finish
//    disposer_thread.join();
//
//    getch(); // Wait for user input
    endwin();

    return 0;
}
