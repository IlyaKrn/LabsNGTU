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

    void printAsCCS(void (*printer)(T item));
    void printAsMatrix(void (*printer)(T item), T zeroElement);
    void getEvenIndexElements(void (*printer)(T item));
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
        LJ.pushBack(LI.getSize() + 1);
        for (int j = 0; j < height; ++j) {
            T* item = matrix.getItemPtr(j)->getItemPtr(i);
            if(*item != zeroElement) {
                values.pushBack(*item);
                LI.pushBack(j + 1);
            }
        }
    }
    LJ.pushBack(LI.getSize() + 1);
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
void CCSMatrix<T>::printAsCCS(void (*printer)(T)) {
    std::cout << "values: " << std::endl;
    values.print(printer);
    auto printerInt = [](int i){
        std::cout << i << " ";
    };
    std::cout << "LI: " << std::endl;
    LI.print(printerInt);
    std::cout << "LJ: " << std::endl;
    LJ.print(printerInt);
}

template<typename T>
void CCSMatrix<T>::printAsMatrix(void (*printer)(T), T zeroElement) {
    std::cout << "Matrix: " << std::endl;

    int width = LJ.getSize() - 1;
    int height = 0;
    for (int i = 0; i < LI.getSize(); ++i) {
        if(height < *LI.getItemPtr(i)){
            height = *LI.getItemPtr(i);
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            bool isZero = true;
            for (int k = *LJ.getItemPtr(j) - 1; k < *LJ.getItemPtr(j + 1) - 1; ++k) {
                if(*LI.getItemPtr(k) == i + 1){
                    isZero = false;
                    printer(*values.getItemPtr(k));
                }
            }
            if(isZero){
                printer(zeroElement);
            }

        }
        std::cout << std::endl;
    }
}

template<typename T>
void CCSMatrix<T>::getEvenIndexElements(void (*printer)(T)) {
    std::cout << "Elements: " << std::endl;
    for (int i = 0; i < values.getSize(); ++i) {
        int y = *LI.getItemPtr(i);
        int x;
        for (int j = 0; j < LJ.getSize(); ++j) {
            if(*LJ.getItemPtr(j) > i + 1)
                break;
                x = j + 1;
        }
        if((x + y) % 2 == 0) {
            std::cout << x << ", " << y << ": ";
            printer(*values.getItemPtr(i));
            std::cout << std::endl;
        }
    }
}
