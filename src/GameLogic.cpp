#include "../include/GameLogic.h"


void printFieldDebug(FieldMatrix* field, int sizeX, int sizeY) {
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            cell* c = field->getPtr(x, y);
            if (c != nullptr) {
                if (c->state == BLACK) {
                    std::cout << "○ ";
                } else if (c->state == WHITE) {
                    std::cout << "● ";
                } else {
                    switch (c->lineIn) {
                        case RIGHT:
                            switch (c->lineOut) {
                                case LEFT:
                                    std::cout << "- ";
                                    break;
                                case TOP:
                                    std::cout << "\\ ";
                                    break;
                                case BOTTOM:
                                    std::cout << "/ ";
                                    break;
                                default:
                                    std::cout << "  ";
                            }
                            break;
                        case LEFT:
                            switch (c->lineOut) {
                                case RIGHT:
                                    std::cout << "- ";
                                    break;
                                case TOP:
                                    std::cout << "/ ";
                                    break;
                                case BOTTOM:
                                    std::cout << "\\ ";
                                    break;
                                default:
                                    std::cout << "  ";
                            }
                            break;
                        case TOP:
                            switch (c->lineOut) {
                                case RIGHT:
                                    std::cout << "\\ ";
                                    break;
                                case LEFT:
                                    std::cout << "/ ";
                                    break;
                                case BOTTOM:
                                    std::cout << "| ";
                                    break;
                                default:
                                    std::cout << "  ";
                            }
                            break;
                        case BOTTOM:
                            switch (c->lineOut) {
                                case RIGHT:
                                    std::cout << "/ ";
                                    break;
                                case LEFT:
                                    std::cout << "\\ ";
                                    break;
                                case TOP:
                                    std::cout << "| ";
                                    break;
                                default:
                                    std::cout << "  ";
                            }
                            break;
                        default:
                            std::cout << "  ";
                    }
                }
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int GameLogic::checkCell(int x, int y, cellSide from, cell* prevCell, lineType typeOfLine) {

    printFieldDebug(fieldMatrix, width, height);

    if (x < 0 || y < 0 || x >= width || y >= height)
        return -1;

    if (fieldMatrix->getPtr(x, y) == nullptr)
        fieldMatrix->insert(cell(NONE, RIGHT, RIGHT, false), x, y);
    cell* current = fieldMatrix->getPtr(x, y);

    if (current->isLine)
        return -1;

    lineType nextLineType = NO_SPECIFIED;

    if (current->state == cellState::BLACK) {
        if(prevCell != nullptr && isCorner(prevCell->lineIn, prevCell->lineOut))
            return -1;
        typeOfLine = CORNER;
        nextLineType = STRAIGHT;
    }

    if (current->state == cellState::WHITE) {
        if(prevCell != nullptr && !isCorner(prevCell->lineIn, prevCell->lineOut))
            nextLineType = CORNER;
        typeOfLine = STRAIGHT;
    }

    current->isLine = true;
    current->lineIn = from;

    LinkedList<cellSide> allowedOuts = LinkedList<cellSide>();
    switch (typeOfLine) {
        case STRAIGHT:
            allowedOuts.pushBack(getOppositeTo(from));
            break;
        case CORNER:
            switch (from) {
                case LEFT:
                case RIGHT:
                    allowedOuts.pushBack(getOppositeTo(TOP));
                    allowedOuts.pushBack(getOppositeTo(BOTTOM));
                    break;
                case TOP:
                case BOTTOM:
                    allowedOuts.pushBack(getOppositeTo(LEFT));
                    allowedOuts.pushBack(getOppositeTo(RIGHT));
                    break;
            }
            break;
        case NO_SPECIFIED:
            if (from != LEFT)
                allowedOuts.pushBack(getOppositeTo(LEFT));
            if (from != RIGHT)
                allowedOuts.pushBack(getOppositeTo(RIGHT));
            if (from != TOP)
                allowedOuts.pushBack(getOppositeTo(TOP));
            if (from != BOTTOM)
                allowedOuts.pushBack(getOppositeTo(BOTTOM));
            break;
    }

    int result = -1;
    for (int i = 0; i < allowedOuts.getSize(); i++) {
        cellSide to = *allowedOuts.getItemPtr(i);

        current->lineOut = to;
        int nextX = x;
        int nextY = y;
        if (to == RIGHT) nextX++;
        if (to == LEFT) nextX--;
        if (to == TOP) nextY--;
        if (to == BOTTOM) nextY++;
        cellSide nextFrom = getOppositeTo(to);

        cell* nextCell = fieldMatrix->getPtr(nextX, nextY);
        if (nextCell != nullptr && nextCell->isLine && nextCell->lineIn == nextFrom) {
            bool fl = true;
            for (int i = 0; i < fieldMatrix->getValuesPtr()->getSize(); ++i) {
                cell* it = fieldMatrix->getValuesPtr()->getItemPtr(i);
                if (it->state == WHITE || it->state == BLACK){
                    if (!it->isLine){
                        fl = false;
                        break;
                    }
                }
            }
            if (fl)
                return 0;
        }

        result = checkCell(nextX, nextY, nextFrom, current, nextLineType);

        if (result != -1)
            break;

    }

    if (result == -1){
        current->isLine = false;
        if(current->state == NONE)
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
        if (checkCell(x, y, from, nullptr, NO_SPECIFIED) != -1)
            return;
    }
}

GameLogic::GameLogic(FieldMatrix* fieldMatrix, int height, int width) {
    this->height = height;
    this->width = width;
    this->fieldMatrix = fieldMatrix;
}
