#pragma once

#include <iostream>
#include "LinkedList.h"


template<typename T>
class CCSMatrix {

private:

    LinkedList<LinkedList<T>> values;
    LinkedList<LinkedList<int>> LI;
    LinkedList<LinkedList<int>> LJ;

public:
    CCSMatrix(LinkedList<LinkedList<int>> matrix, int height, int width);

    ~CCSMatrix();


    void clear();

    void print(void (*printer)(T item));
};

template<typename T>
CCSMatrix<T>::CCSMatrix(LinkedList<LinkedList<int>> matrix, int height, int width) {

}

template<typename T>
CCSMatrix<T>::~CCSMatrix() = default;

template<typename T>
void CCSMatrix<T>::clear() {
    values.clear();
    LI.clear();
    LJ.clear();
}

template<typename T>
void CCSMatrix<T>::print(void (*printer)(T)) {

}
