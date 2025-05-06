cmake_minimum_required(VERSION 3.5)
project(lab1)

set(SOURCES
        main.cpp
        include/FieldMatrix.h
        include/GameLogic.h
        include/LinkedList.h
        src/FieldMatrix.cpp
        src/GameLogic.cpp
)

add_executable(main ${SOURCES})

target_include_directories(main
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)