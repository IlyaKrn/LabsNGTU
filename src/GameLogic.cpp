#include "../include/GameLogic.h"

int GameLogic::checkCell(int x, int y, cellSide from, cell* prevCell, bool isMustBeCorner) {
    if (x < 0 || y < 0 || x >= height || y >= width)
        return -1;

    if (fieldMatrix->getPtr(x, y) == nullptr)
        fieldMatrix->insert(cell(NONE, TOP, TOP, false), x, y);
    cell* current = fieldMatrix->getPtr(x, y);

    if (current->isLine)
        return -1;

    bool isNextMustBeCorner = false;

    if (current->state == cellState::BLACK) {
        if(prevCell != nullptr && isCorner(prevCell->lineIn, prevCell->lineOut))
            return -1;
        isMustBeCorner = true;
    }

    if (current->state == cellState::WHITE) {
        if(prevCell != nullptr && !isCorner(prevCell->lineIn, prevCell->lineOut))
            isNextMustBeCorner = true;
    }

    current->isLine = true;
    current->lineIn = from;

    int result = -1;
    for (cellSide to : {LEFT, RIGHT, TOP, BOTTOM}) {
        if(to != from){
            current->lineOut = to;
            int nextX = x;
            int nextY = y;
            if (to == RIGHT) nextX++;
            if (to == LEFT) nextX--;
            if (to == TOP) nextY++;
            if (to == BOTTOM) nextY--;
            cellSide nextFrom = getOppositeTo(to);

            cell* nextCell = fieldMatrix->getPtr(nextX, nextY);
            if (nextCell != nullptr && nextCell->isLine && nextCell->lineIn == getOppositeTo(to))
                return 0;

            if (isMustBeCorner){
                if (isCorner(from, to)){
                    result = checkCell(nextX, nextY, nextFrom, current, isNextMustBeCorner);
                }
            } else {
                result = checkCell(nextX, nextY, nextFrom, current, isNextMustBeCorner);
            }
            if (result != -1)
                break;

        }
    }

    if (result == -1){
        current->isLine = false;
        if (current->state == NONE)
            fieldMatrix->remove(x, y);
    }

    return result;
}

cellSide GameLogic::getOppositeTo(cellSide side){
    if (side == RIGHT) return LEFT;
    if (side == LEFT) return RIGHT;
    if (side == TOP) return BOTTOM;
    if (side == BOTTOM) return TOP;
}

bool GameLogic::isCorner(cellSide side1, cellSide side2){
    if (side1 == RIGHT || side1 == LEFT) return side2 == TOP || side2 == BOTTOM;
    if (side1 == TOP || side1 == BOTTOM) return side2 == RIGHT || side2 == LEFT;
}

void GameLogic::getSolution(){
    int x = -1;
    int y = -1;

    fieldMatrix->getFirstFilledCell(&x, &y);
    if (x == -1)
        return;

    for (cellSide from : {LEFT, RIGHT, TOP, BOTTOM}) {
        if (checkCell(x, y, from, nullptr, false) != -1)
            return;
    }
}

GameLogic::GameLogic(FieldMatrix* fieldMatrix, int height, int width) {
    this->height = height;
    this->width = width;
    this->fieldMatrix = fieldMatrix;
}
