#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <mutex>
#include <condition_variable>
#include "Destination.h"
#include "Disposer.h"

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
    bool is_running;

    static std::vector<char> alphabet;

public:
    Client(int y_client_start, int x_client_start, int _destination, int &_disposer_destination, Disposer &_disposer, std::vector<Destination> &_destinations, std::mutex &mutex, std::condition_variable &cond_var, std::vector<Client*> &clients);

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
    void move(int &_current_destination, Disposer &_disposer, std::vector<Destination> &_destinations, std::mutex &mutex, std::condition_variable &cond_var, std::vector<Client*> &clients);

    std::thread client_thread;
};

#endif //MULTITHREADING_PROJECT_CLIENT_H
