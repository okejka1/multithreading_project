//
// Created by okejka on 04.04.24.
//

#include "Destination.h"


Destination::Destination(int y_coordinate, int x_coordinate) {
    y = y_coordinate;
    x = x_coordinate;
}

void Destination::draw_borders() {
    mvprintw(y + 1, x, "%c", '-');
    mvprintw(y - 1, x, "%c", '-');

}

int Destination::get_x(){
    return x;
}

int Destination::get_y() {
    return y;
}

