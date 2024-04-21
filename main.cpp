#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include "utils/Destination.h"
#include "utils/Client.h"
#include "utils/Disposer.h"

int DIRECTOR_Y = 10;
int DIRECTOR_X = 45;

Destination upper_base(5, 60);
Destination middle_base(10, 60);
Destination lower_base(15, 60);
Disposer dispo(10,45);

std::vector<Client> clients;
std::vector<Destination> destinations{upper_base, middle_base, lower_base};
bool end_condition = false;
int disposer_destination = 0;


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
        upper_base.draw_borders();
        middle_base.draw_borders();
        lower_base.draw_borders();

        // Print the disposer arrow based on current disposer_destination
        print_disposer(disposer_destination);

        // Refresh the screen
        refresh();

        sleep(1);

        // Check if the disposer thread has finished
        if (end_condition)
            break;
    }
}



int main() {

    initscr();
    std::thread disposer_thread(disposer, std::ref(end_condition));
    display_all();

//
//    int y = 10;
//    int x = 10;
//    Client client(1,10,10,-1);
////    mvprintw(client.get_y(),client.get_x(),"%c", client.get_sign());
//    clients.push_back(client);
//    display();
//    while() {
//        clear();
//        upper_base.draw_borders();
//        middle_base.draw_borders();
//        lower_base.draw_borders();
//        mvprintw(y, x + i, "%c", '$');
//
//        sleep(1);
//        refresh();
//    }

    disposer_thread.join();
    getch(); // Wait for user input

    endwin();

    return 0;
}
