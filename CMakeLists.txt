cmake_minimum_required(VERSION 3.7)
project(GoL)

set(CMAKE_CXX_STANDARD 11)

add_executable(GoL main.cpp Game.cpp Game.h Menu.cpp Menu.h structures/structure.cpp structures/structure.h
        structures/ds_structure_types.h structures/ds_routines.cpp structures/ds_routines.h structures/vector.cpp
        structures/vector.h structures/array.h structures/matrix.h structures/ArrayMatrix.h)