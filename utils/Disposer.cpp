//
// Created by okejka on 21.04.24.
//

#include "Disposer.h"

Disposer::Disposer(int y, int x) : y(y), x(x) {}

int Disposer::get_y() const {
    return y;
}

int Disposer::get_x() const {
    return x;
}
