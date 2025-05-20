#pragma once

#include "LinkedList.h"

/*
 * cellState - состояния клетки
 * */
enum cellState {
    WHITE, BLACK, NONE
};

/*
 * cellSide - стороны клетки
 * */
enum cellSide {
    LEFT, RIGHT, TOP, BOTTOM
};

/*
 * cell - структура клетки
 * state - текущее состояние
 * lineIn - сторона входа линии
 * lineOut - сторона выхода линии
 * isLine - отметка о прохождении линии
 * */
struct cell{
    cellState state;
    cellSide lineIn;
    cellSide lineOut;
    bool isLine;

    cell();
    cell(cellState state, cellSide lineIn, cellSide lineOut, bool isLine);

};

/*
 * FieldMatrix - разреженная матрица для хранения игрового поля
 * values - список значений
 * coordX - список координат X
 * coordY - список координат Y
 * insert - метод вставки элемента по координатам
 * remove - метод удаления элемента по координатам
 * getPtr - метод получения указателя на элемент по координатам
 * getFirstFilledCell - метод получения координат на первой жемчужины
 * getValuesPtr - метод получения указателя на список значений
 * */
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

    LinkedList<cell>* getValuesPtr();

};