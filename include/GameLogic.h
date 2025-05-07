#pragma once

#include "FieldMatrix.h"

enum lineType{
    CORNER, STRAIGHT, NO_SPECIFIED
};

class GameLogic {
private:
    FieldMatrix* fieldMatrix;
    int height;
    int width;

    int checkCell(int x, int y, cellSide from, cell* prevCell, lineType lineType);
    cellSide getOppositeTo(cellSide side);
    bool isCorner(cellSide side1, cellSide side2);

public:
    GameLogic(FieldMatrix* fieldMatrix, int height, int width);

    void getSolution();
};
