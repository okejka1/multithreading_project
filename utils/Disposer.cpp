//
// Created by okejka on 12.04.24.
//

#include "Disposer.h"

Disposer::Disposer(int y_coordinate, int x_coordinate) {
    y = y_coordinate;
    x = x_coordinate;

}

int Disposer::get_y() const {
    return y;
}

int Disposer::get_x() const {
    return x;
}
