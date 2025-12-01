cmake_minimum_required(VERSION 3.5)
project(lab1)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

add_executable(main
        main.cpp
        include/SLAU.h
        src/SLAU.cpp
)