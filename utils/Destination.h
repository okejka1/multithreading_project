//
// Created by okejka on 04.04.24.
//
#include <ncurses.h>
#include <unistd.h>

#ifndef MULTITHREADING_PROJECT_DESTINATION_H
#define MULTITHREADING_PROJECT_DESTINATION_H


class Destination {
private:
    int x;
    int y;
public:

    Destination(int y, int x);
    void draw_borders();
    int get_x();
    int get_y();
};


#endif //MULTITHREADING_PROJECT_DESTINATION_H
