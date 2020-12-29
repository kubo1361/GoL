cmake_minimum_required(VERSION 3.7)
project(client)

set(CMAKE_CXX_STANDARD 14)

add_executable(client main.cpp Connection.h Connection.cpp)