cmake_minimum_required(VERSION 3.7)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server
        main.cpp
        Connection.cpp
        Connection.h
        Clients.cpp
        Clients.h
        connectionHandlerThread.h
        readClientInputThread.h
        processingThread.h
        Game.cpp
        Game.h)

target_link_libraries(Server pthread ncurses)

