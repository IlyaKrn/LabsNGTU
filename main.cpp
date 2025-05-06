#include "include/FieldMatrix.h"
#include <iostream>

// Вспомогательная функция для печати поля
void printField(FieldMatrix field, int sizeX, int sizeY) {
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            cell* c = field.getPtr(x, y);
            if (c != nullptr) {
                if (c->state == BLACK) {
                    std::cout << "● ";
                } else if (c->state == WHITE) {
                    std::cout << "○ ";
                } else {
                    std::cout << ". ";
                }
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    FieldMatrix field;

    // Заполняем поле жемчужинами (пример из классической головоломки Masyu)
    field.insert(cell(BLACK, RIGHT, RIGHT, false), 0, 0);
    field.insert(cell(WHITE, RIGHT, RIGHT, false), 2, 0);
    field.insert(cell(BLACK, RIGHT, RIGHT, false), 4, 0);

    field.insert(cell(WHITE, RIGHT, RIGHT, false), 0, 2);
    field.insert(cell(BLACK, RIGHT, RIGHT, false), 2, 2);
    field.insert(cell(WHITE, RIGHT, RIGHT, false), 4, 2);

    field.insert(cell(BLACK, RIGHT, RIGHT, false), 0, 4);
    field.insert(cell(WHITE, RIGHT, RIGHT, false), 2, 4);
    field.insert(cell(BLACK, RIGHT, RIGHT, false), 4, 4);

    std::cout << "Игровое поле (5x5):" << std::endl;
    printField(field, 5, 5);

    return 0;
}