//
// Created by okejka on 21.04.24.
//

#ifndef MULTITHREADING_PROJECT_DISPOSER_H
#define MULTITHREADING_PROJECT_DISPOSER_H


class Disposer {
private:
    int y;
    int x;
public:
    Disposer(int y, int x);

    int get_y() const;

    int get_x() const;

};


#endif //MULTITHREADING_PROJECT_DISPOSER_H
