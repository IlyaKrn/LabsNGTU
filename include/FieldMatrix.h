#pragma once

#include "LinkedList.h"

enum cellState {
    WHITE, BLACK, NONE
};

enum cellSide {
    LEFT, RIGHT, TOP, BOTTOM
};

struct cell{
    cellState state;
    cellSide lineIn;
    cellSide lineOut;
    bool isLine;

    cell();
    cell(cellState state, cellSide lineIn, cellSide lineOut, bool isLine);

};

class FieldMatrix {
private:

    LinkedList<cell> values;
    LinkedList<int> coordX;
    LinkedList<int> coordY;

public:

    void insert(cell data, int x, int y);
    void remove(int x, int y);
    cell* getPtr(int x, int y);
    void getFirstFilledCell(int* x, int* y);

};