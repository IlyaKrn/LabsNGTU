cmake_minimum_required(VERSION 3.5)
project(lab1)

set(SOURCES
#        main.cpp
        test.cpp
)

add_executable(main ${SOURCES})

target_include_directories(main
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)