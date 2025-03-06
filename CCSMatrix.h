#pragma once

#include <iostream>
#include "LinkedList.h"


template<typename T>
class CCSMatrix {

private:

    LinkedList<T> values;
    LinkedList<int> LI;
    LinkedList<int> LJ;

public:
    CCSMatrix(LinkedList<LinkedList<T>> matrix, int height, int width, T zeroElement);

    ~CCSMatrix();


    void clear();

    void print(void (*printer)(T item));
};

template<typename T>
CCSMatrix<T>::CCSMatrix(LinkedList<LinkedList<T>> matrix, int height, int width, T zeroElement) {
    if(matrix.getSize() != width) {
        throw std::string("can not translate matrix to ccs format");
    }
    for (int i = 0; i < width; ++i) {
        LinkedList<T>* col = matrix.getItemPtr(i);
        if(col->getSize() != height) {
            throw std::string("can not translate matrix to ccs format");
        }
    }
    for (int i = 0; i < width; ++i) {
        LJ.pushBack(LI.getSize());
        for (int j = 0; j < height; ++j) {
            T* item = matrix.getItemPtr(j)->getItemPtr(i);
            if(*item != zeroElement) {
                values.pushBack(*item);
                LI.pushBack(j);
            }
        }
    }
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
    std::cout << "values: " << std::endl;
    values.print(printer);
    std::cout << "LI: " << std::endl;
    LI.print(printer);
    std::cout << "LJ: " << std::endl;
    LJ.print(printer);
}
