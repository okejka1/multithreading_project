//
// Created by okejka on 12.04.24.
//

#ifndef MULTITHREADING_PROJECT_DISPOSER_H
#define MULTITHREADING_PROJECT_DISPOSER_H


class Disposer {
private:
    int y;
    int x;

public:
    int get_y() const;

    int get_x() const;

    Disposer(int y_coordinate, int x_coordinate);

};


#endif //MULTITHREADING_PROJECT_DISPOSER_H
