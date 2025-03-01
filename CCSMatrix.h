#pragma once

#include <iostream>


template<typename T>
class CCSMatrix {

public:
    CCSMatrix();

    ~CCSMatrix();

    void clear();

    void print(void (*printer)(T item));
};