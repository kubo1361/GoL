cmake_minimum_required(VERSION 3.7)
project(Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(Client main.cpp Connection.cpp Game.cpp Menu.cpp Game.h Menu.h Connection.h pThread.h rThread.h)
target_link_libraries(Client pthread ncurses)