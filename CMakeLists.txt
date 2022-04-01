cmake_minimum_required(VERSION 3.16)
project(Q_opt)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Q_opt
        main.cpp
        src/Circuit.cpp headers/Circuit.h
        src/Oracle.cpp headers/Oracle.h
        src/Template.cpp headers/Template.h
        src/Match.cpp headers/Match.h)
