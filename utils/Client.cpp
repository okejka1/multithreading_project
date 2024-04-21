

#include "Client.h"
#include "Disposer.h"

std::vector<char> Client::alphabet{'@', '#', '$', '&', '(', ')', '!'};


Client::Client(int id_client, int y_client_start, int x_client_start, int _destination) {
    id = id_client;
    y = y_client_start;
    x = x_client_start;
    destination = _destination;

    // gets 'entropy' from device that generates random numbers itself
    // to seed a mersenne twister (pseudo) random generator
    std::mt19937 generator(std::random_device{}());

    // make sure all numbers have an equal chance.
    // range is inclusive (so we need -1 for vector index)
    std::uniform_int_distribution<std::size_t> distribution(0, alphabet.size() - 1);

    sign = alphabet[distribution(generator)];

}

int Client::get_id() const {
    return id;
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




}


