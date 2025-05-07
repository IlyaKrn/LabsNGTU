#include "include/FieldMatrix.h"
#include "include/GameLogic.h"
#include <iostream>

// Вспомогательная функция для печати поля
void printField(FieldMatrix* field, int sizeX, int sizeY) {
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
}

int main() {
    FieldMatrix* field = new FieldMatrix();

//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 2, 0);
//    field->insert(cell(BLACK, RIGHT, RIGHT, false), 5, 0);
//
//    field->insert(cell(BLACK, RIGHT, RIGHT, false), 0, 2);
//    field->insert(cell(BLACK, RIGHT, RIGHT, false), 3, 2);
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 4, 2);
//    field->insert(cell(BLACK, RIGHT, RIGHT, false), 7, 2);
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 9, 2);
//
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 6, 3);
//
//    field->insert(cell(BLACK, RIGHT, RIGHT, false), 2, 4);
//    field->insert(cell(BLACK, RIGHT, RIGHT, false), 7, 4);
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 8, 4);
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 9, 4);
//
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 5, 5);
//
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 1, 6);
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 3, 6);
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 6, 6);
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 7, 6);
//
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 1, 7);
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 4, 7);
//
//    field->insert(cell(BLACK, RIGHT, RIGHT, false), 8, 8);
//
//    field->insert(cell(BLACK, RIGHT, RIGHT, false), 0, 9);
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 2, 9);
//    field->insert(cell(WHITE, RIGHT, RIGHT, false), 5, 9);



    field->insert(cell(BLACK, RIGHT, RIGHT, false), 2, 2);
    field->insert(cell(BLACK, RIGHT, RIGHT, false), 0, 0);

    GameLogic gl(field, 5, 5);
    gl.getSolution();

    printField(field, 5, 5);
    delete field;
    return 0;
}