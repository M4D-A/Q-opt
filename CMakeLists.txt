cmake_minimum_required(VERSION 3.16)
project(Q_opt)

set(CMAKE_CXX_STANDARD 14)

add_executable(Q_opt src/main.cpp
        src/Circuit.cpp src/Circuit.h
        src/Oracle.cpp src/Oracle.h
        src/Auxiliary.cpp src/Auxiliary.h src/Template.cpp src/Template.h)
