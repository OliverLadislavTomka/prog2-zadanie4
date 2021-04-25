cmake_minimum_required(VERSION 3.19)
project(prog2_zadanie4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(prog2_zadanie4
        data.c
        data.h
        main.c
        rng.c
        rng.h)
