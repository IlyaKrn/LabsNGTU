#include "../include/GameLogic.h"

int GameLogic::checkCell(int x, int y, cellSide from, cell* prevCell, lineType typeOfLine, int pearlsReached) {
    if (x < 0 || y < 0 || x >= width || y >= height)
        return -1;

    cell* current = fieldMatrix->getPtr(x, y);
    if (current == nullptr) {
        fieldMatrix->insert(cell(NONE, RIGHT, RIGHT, false), x, y);
        current = fieldMatrix->getPtr(x, y);
    }
    else if (current->isLine){
        if (current->lineIn == from){
            if(current->state == BLACK && (isCorner(prevCell->lineIn, prevCell->lineOut) || typeOfLine == STRAIGHT))
                return -1;
            if(current->state == WHITE && typeOfLine == CORNER)
                return -1;
            if (current->state == WHITE && !isCorner(prevCell->lineIn, prevCell->lineOut)){
                int nextX = x;
                int nextY = y;
                switch (current->lineOut) {
                    case RIGHT:
                        nextX++;
                        break;
                    case LEFT:
                        nextX--;
                        break;
                    case TOP:
                        nextY--;
                        break;
                    case BOTTOM:
                        nextY++;
                        break;
                }
                cell* nextCell = fieldMatrix->getPtr(nextX, nextY);
                if(!isCorner(nextCell->lineIn, nextCell->lineOut))
                    return -1;
            }
            if (pearlsAll == pearlsReached)
                return 0;
            else
                return -1;
        } else{
            return -1;
        }
    }

    lineType nextLineType;
    switch (current->state) {
        case WHITE:
            if (typeOfLine == CORNER)
                return -1;
            if(prevCell != nullptr && !isCorner(prevCell->lineIn, prevCell->lineOut))
                nextLineType = CORNER;
            typeOfLine = STRAIGHT;
            break;
        case BLACK:
            if (typeOfLine == STRAIGHT)
                return -1;
            if(prevCell != nullptr && isCorner(prevCell->lineIn, prevCell->lineOut))
                return -1;
            typeOfLine = CORNER;
            nextLineType = STRAIGHT;
            break;
        default:
            nextLineType = NO_SPECIFIED;
    }
    current->isLine = true;
    current->lineIn = from;

    int result = -1;
    for (cellSide to : {RIGHT, LEFT, TOP, BOTTOM}) {
        if (to == from || (typeOfLine == STRAIGHT && to != getOppositeTo(from)) || (typeOfLine == CORNER && !isCorner(from, to)))
            continue;

        current->lineOut = to;
        int nextX = x;
        int nextY = y;
        switch (to) {
            case RIGHT:
                nextX++;
                break;
            case LEFT:
                nextX--;
                break;
            case TOP:
                nextY--;
                break;
            case BOTTOM:
                nextY++;
                break;
        }
        cellSide nextFrom = getOppositeTo(to);

        result = checkCell(nextX, nextY, nextFrom, current, nextLineType, ((current->state == WHITE || current->state == BLACK) ? pearlsReached + 1 : pearlsReached));

        if (result != -1)
            break;

    }

    if (result == -1){
        current->isLine = false;
    }

    return result;
}

cellSide GameLogic::getOppositeTo(cellSide side){
    switch (side) {
        case RIGHT:
            return LEFT;
        case LEFT:
            return RIGHT;
        case TOP:
            return BOTTOM;
        case BOTTOM:
            return TOP;
    }
}

bool GameLogic::isCorner(cellSide side1, cellSide side2){
    switch (side1) {
        case RIGHT:
        case LEFT:
            return side2 == TOP || side2 == BOTTOM;
        case TOP:
        case BOTTOM:
            return side2 == RIGHT || side2 == LEFT;
    }
}

void GameLogic::getSolution(){
    for (int i = 0; i < fieldMatrix->getValuesPtr()->getSize(); ++i) {
        fieldMatrix->getValuesPtr()->getItemPtr(i)->isLine = false;
    }
    int x = -1;
    int y = -1;

    fieldMatrix->getFirstFilledCell(&x, &y);
    if (x == -1)
        return;

    pearlsAll = 0;
    for (int i = 0; i < fieldMatrix->getValuesPtr()->getSize(); ++i) {
        cell* it = fieldMatrix->getValuesPtr()->getItemPtr(i);
        if (it->state == WHITE || it->state == BLACK){
            pearlsAll++;
        }
    }
    for (cellSide from : {LEFT, RIGHT, TOP, BOTTOM}) {
        if (checkCell(x, y, from, nullptr, NO_SPECIFIED, 0) != -1)
            return;
    }
}

GameLogic::GameLogic(FieldMatrix* fieldMatrix, int height, int width) {
    this->height = height;
    this->width = width;
    this->fieldMatrix = fieldMatrix;
}
