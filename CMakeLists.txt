cmake_minimum_required(VERSION 3.30)
project(blackJack)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(blackJack
    black_jack.cpp
    bj_classes.cpp
    bj_functions.cpp)
