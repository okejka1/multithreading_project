//
// Created by okejka on 03.04.24.
//
#include "vector"
#include "Destination.h"
#include "Disposer.h"
#include <random>

#ifndef MULTITHREADING_PROJECT_CLIENT_H
#define MULTITHREADING_PROJECT_CLIENT_H


class Client {
private:
    char sign;
    int x;
    int y;
    int destination;
    int speed;
    bool arrived;
    bool to_erased;
    std::thread client_thread;

    static std::vector<char> alphabet;
public:


    Client(int y_client_start, int x_client_start, int _destination, int &_current_destination, Disposer &_disposer, std::vector<Destination> &_destinations);

    bool is_to_erased() const;

    void set_to_erased(bool to_erased);

    bool is_arrived() const;

    void set_arrived(bool arrived);

    int get_speed() const;

    char get_sign() const;

    int get_x() const;

    int get_y() const;

    int get_destination() const;

    void set_x(int _x);

    void set_y(int _y);

    void set_destination(int _destination);


    void move(int _current_destination, Disposer &_disposer, std::vector<Destination> &_destinations);
};


#endif //MULTITHREADING_PROJECT_CLIENT_H
