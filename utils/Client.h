//
// Created by okejka on 03.04.24.
//
#include "vector"
#include <random>

#ifndef MULTITHREADING_PROJECT_CLIENT_H
#define MULTITHREADING_PROJECT_CLIENT_H


class Client {
private:
    int id;
    char sign;
    int x;
    int y;
    int destination;
    static std::vector<char> alphabet;
public:


    Client(int id_client,int y_client_start, int x_client_start, int _destination);

    int get_id() const;

    char get_sign() const;

    int get_x() const;

    int get_y() const;

    int get_destination() const;

    void set_x(int _x);

    void set_y(int _y);

    void set_destination(int _destination);
};


#endif //MULTITHREADING_PROJECT_CLIENT_H
