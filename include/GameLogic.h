#pragma once

#include "FieldMatrix.h"

/*
 * lineType - типы линий
 * */
enum lineType{
    CORNER, STRAIGHT, NO_SPECIFIED
};

/*
 * GameLogic - класс для выполнения логики игры
 * fieldMatrix - поле с элементами
 * height - высота поля
 * width - ширина поля
 * pearlsAll - общее колличество жемчужин на поле
 * checkCell - метод рекурсивной проверки всех возможных линий
 * getOppositeTo - метод получения противоположной стороны
 * isCorner - метод проверки двух сторон на образование угла
 * getSolution - метод построения линии
 * */
class GameLogic {
private:
    FieldMatrix* fieldMatrix;
    int height;
    int width;
    int pearlsAll;

    int checkCell(int x, int y, cellSide from, cell* prevCell, lineType lineType, int pearlsReached);
    cellSide getOppositeTo(cellSide side);
    bool isCorner(cellSide side1, cellSide side2);

public:
    GameLogic(FieldMatrix* fieldMatrix, int height, int width);

    void getSolution();
};
