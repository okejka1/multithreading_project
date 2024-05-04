

#include <iostream>
#include <thread>
#include <chrono>
#include "Client.h"
#include "Disposer.h"

std::vector<char> Client::alphabet{'@', '#', '$', '&', '(', ')', '!'};


Client::Client(int y_client_start, int x_client_start, int _destination) {
    y = y_client_start;
    x = x_client_start;
    destination = _destination;
    arrived = false;
    to_erased = false;
    client_thread(&Client::move, this);


    // gets 'entropy' from device that generates random numbers itself
    // to seed a mersenne twister (pseudo) random generator
    std::mt19937 generator(std::random_device{}());

    // make sure all numbers have an equal chance.
    // range is inclusive (so we need -1 for vector index)
    std::uniform_int_distribution<std::size_t> dist_alphabet(0, alphabet.size() - 1);
    std::uniform_int_distribution<> dist_speed(0,4);

    sign = alphabet[dist_alphabet(generator)];
    speed = dist_speed(generator);




}



char Client::get_sign() const {
    return sign;
}

int Client::get_x() const {
    return x;
}

int Client::get_y() const {
    return y;
}

int Client::get_destination() const {
    return destination;
}

void Client::set_x(int _x) {
    x = _x;
}

void Client::set_y(int _y) {
    y = _y;
}

void Client::set_destination(int _destination) {
    destination = _destination;
}

void Client::move(int _current_destination, Disposer &_disposer, std::vector<Destination> &_destinations) {
    // Check if the client is not at the disposer's position

    // situations
    // still not at the disposer
    // at the coordinates of disposer -> given final destination
    // get y of final destination
    // get x of final destination
    // if at final destination mark client to be deleted after some time


    if (destination == -1 && x < _disposer.get_x()) {
        x++;
    } else if (this->destination == -1 && x == _disposer.get_x()) {
        this->destination = _current_destination;
    }
    if(arrived) {
        std::this_thread::sleep_for(std::chrono::seconds(2));


    }

    switch (destination) {
        case 0:
            if (y >_destinations[0].get_y()) {
                y--;
            } else {
                if(x < _destinations[0].get_x()) {
                    x++;

                } else {
                    arrived = true;
                }
            }
            break;
        case 1:
            if (x < _destinations[1].get_x()){
                x++;
            } else {
                arrived = true;
            }
            break;
        case 2:
            if (y < _destinations[2].get_y()) {
                y++;
            }
            else if(x < _destinations[2].get_x()) {
                x++;
            } else {
                arrived = true;
            }
            break;
        default:
            std::cout << "\nlol\n";
            break;
    }
    std::cout << "Current x: y:" << x << " " << y << "dest:" << destination;

}

int Client::get_speed() const {
    speed;
}





