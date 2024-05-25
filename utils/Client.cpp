#include <algorithm>
#include "Client.h"

std::vector<char> Client::alphabet{'@', '#', '$', '&', '(', ')', '!'};

Client::Client(int y_client_start, int x_client_start, int _destination, int &_disposer_destination, Disposer &_disposer, std::vector<Destination> &_destinations, std::mutex &mutex, std::condition_variable &cond_var, std::vector<Client*> &clients)
        : y(y_client_start), x(x_client_start), destination(_destination), is_running(true), arrived(false), to_erased(false) {

    // Initialize random number generator
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist_alphabet(0, alphabet.size() - 1);
    std::uniform_int_distribution<> dist_speed(1, 3);

    sign = alphabet[dist_alphabet(generator)];
    speed = dist_speed(generator);

    client_thread = std::thread(&Client::move, this, std::ref(_disposer_destination), std::ref(_disposer), std::ref(_destinations), std::ref(mutex), std::ref(cond_var), std::ref(clients));
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

bool Client::is_occupied(std::vector<Client*> &clients, int &_current_destination) {
    for(Client * &client: clients) {
        if(client->get_destination() == _current_destination)
        return true;
    }
        return false;
}

void Client::move(int &_current_destination, Disposer &_disposer, std::vector<Destination> &_destinations, std::mutex &_mutex, std::condition_variable &cond_var, std::vector<Client*> &clients) {
    while (is_running) {
        {
            std::unique_lock<std::mutex> lock(_mutex);
            if (destination == -1) {
                // Move towards the disposer
                if (x < _disposer.get_x() - 1) {
                    x++;
                } else if (x == _disposer.get_x() - 1) {
                    cond_var.wait(lock, [this, &_current_destination] {
                        return destination == _current_destination;
                    });
                }

            }
        }

        if (arrived && !to_erased) {
            std::this_thread::sleep_for(std::chrono::seconds(4));
            is_running = false;
            to_erased = true;
        }

        // Move towards the destination
        switch (destination) {
            case 0:
                if (y > _destinations[0].get_y()) {
                    y--;
                } else {
                    if (x < _destinations[0].get_x()) {
                        x++;
                    } else {
                        arrived = true;
                    }
                }
                break;
            case 1:
                if (x < _destinations[1].get_x()) {
                    x++;
                } else {
                    arrived = true;
                }
                break;
            case 2:
                if (y < _destinations[2].get_y()) {
                    y++;
                } else if (x < _destinations[2].get_x()) {
                    x++;
                } else {
                    arrived = true;
                }
                break;
            default:
                break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(300 / speed));
    }


}

int Client::get_speed() const {
    return speed;
}

bool Client::is_to_erased() const {
    return to_erased;
}

void Client::set_to_erased(bool _to_erased) {
    to_erased = _to_erased;
}

bool Client::is_arrived() const {
    return arrived;
}

void Client::set_arrived(bool _arrived) {
    arrived = _arrived;
}
