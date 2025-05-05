#include "FieldMatrix.h"

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