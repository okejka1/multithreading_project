#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "utils/Destination.h"

#include "utils/Disposer.h"
#include "utils/Client.h"


//const int y_start = 10; // base coordinates where
//const int x_start = 10;






`std::vector<Client> clients;



int main() {
    initscr();

    Destination upper_base(5, 60);
    Destination middle_base(10, 60);
    Destination lower_base(15, 60);
    Disposer disposer(10, 45);


    int y = 10;
    int x = 10;
    Client client(1,10,10,-1);
    mvprintw(client.get_y(),client.get_x(),"%c", client.get_sign());
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

    getch(); // Wait for user input

    endwin();

    return 0;
}
