#pragma once

#include "FieldMatrix.h"

class GameLogic {
private:
    FieldMatrix fieldMatrix;
    int height;
    int width;

    int checkCell(int x, int y, cellSide from, cell* prevCell, bool isMustBeCorner);
    cellSide getOppositeTo(cellSide side);
    bool isCorner(cellSide side1, cellSide side2);

public:
    FieldMatrix* getSolution();
};
