cmake_minimum_required(VERSION 3.16)
project(Q_opt)

set(CMAKE_CXX_STANDARD 14)

add_executable(Q_opt main.cpp Circuit.cpp Circuit.h)
