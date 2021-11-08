cmake_minimum_required(VERSION 3.13)
project(task1_matrix_multplication_Mohamed_Ibrahim_01)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(task1_matrix_multplication_Mohamed_Ibrahim_01
        matrix.cpp
        matrix.h
        naive.cpp
        strassen.cpp
        stress.cpp)
