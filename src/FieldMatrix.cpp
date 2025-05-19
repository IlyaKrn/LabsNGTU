#include "../include/FieldMatrix.h"

void FieldMatrix::insert(cell data, int x, int y) {
    for (int i = 0; i < coordX.getSize(); ++i) {
        if (*coordX.getItemPtr(i) == x && *coordY.getItemPtr(i) == y) {
            *values.getItemPtr(i) = data;
            return;
        }
    }
    values.pushBack(data);
    coordX.pushBack(x);
    coordY.pushBack(y);
}

void FieldMatrix::remove(int x, int y) {
    for (int i = 0; i < coordX.getSize(); ++i) {
        if (*coordX.getItemPtr(i) == x && *coordY.getItemPtr(i) == y) {
            values.remove(i);
            coordX.remove(i);
            coordY.remove(i);
            return;
        }
    }
}

cell* FieldMatrix::getPtr(int x, int y) {
    for (int i = 0; i < coordX.getSize(); ++i) {
        if (*coordX.getItemPtr(i) == x && *coordY.getItemPtr(i) == y) {
            return values.getItemPtr(i);
        }
    }
    return nullptr;
}

void FieldMatrix::getFirstFilledCell(int* x, int* y){
    *x = -1;
    *y = -1;
    for (int i = 0; i < values.getSize(); ++i) {
        if (values.getItemPtr(i)->state != NONE){
            *x = *coordX.getItemPtr(i);
            *y = *coordY.getItemPtr(i);
        }
    }
}

LinkedList<cell>* FieldMatrix::getValuesPtr() {
    return &values;
}

cell::cell(cellState state, cellSide lineIn, cellSide lineOut, bool isLine) : state(state), lineIn(lineIn), lineOut(lineOut), isLine(isLine) {}

cell::cell() {}
