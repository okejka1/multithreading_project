cmake_minimum_required(VERSION 3.17)
project(multithreading_project)

set(CMAKE_CXX_STANDARD 14)

# Find the ncurses library
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(multithreading_project main.cpp
        utils/Client.cpp
        utils/Client.h
        utils/Destination.cpp
        utils/Destination.h
        utils/Disposer.cpp
        utils/Disposer.h
)

# Link against the ncurses library
target_link_libraries(multithreading_project ${CURSES_LIBRARIES})