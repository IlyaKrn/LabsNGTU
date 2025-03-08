#pragma once

#include <iostream>
#include "LinkedList.h"


/*
 * Класс CCSMatrix - разреженная матрица CCS
 * values - список значений
 * LI - список сдвигов значений по y
 * LJ - список сдвигов столбцов в списке значений
 * clear - метод для очистки матрицы, просто чистит списки
 * printAsCCS - метод для вывода матрицы в ccs формате
 * printAsMatrix - метод для вывода матрицы в обычном формате
 * getEvenIndexElements - метод для вывода элементов с четной суммой индексов
 */
template<typename T>
class CCSMatrix {
private:

    LinkedList<T> values;
    LinkedList<int> LI;
    LinkedList<int> LJ;

public:
    CCSMatrix(LinkedList<LinkedList<T>> matrix, int height, int width, T zeroElement);

    ~CCSMatrix();


    void clear();

    void printAsCCS(void (*printer)(T item));
    void printAsMatrix(void (*printer)(T item), T zeroElement);
    void getEvenIndexElements(void (*printer)(T item));
};

/*
 * Конструктор CCSMatrix
 * matrix - исходная матрица в виде вложенных списков
 * height - количество столбцов
 * width - количество строк
 * zeroElement - нулевое значение
 * возвращает исключение при ошибке в матрице
 */
template<typename T>
CCSMatrix<T>::CCSMatrix(LinkedList<LinkedList<T>> matrix, int height, int width, T zeroElement) {
    //проверка на соответствие размеров списков и height/width
    if(matrix.getSize() != width) {
        throw std::string("can not translate matrix to ccs format");
    }
    for (int i = 0; i < width; ++i) {
        LinkedList<T>* col = matrix.getItemPtr(i);
        if(col->getSize() != height) {
            throw std::string("can not translate matrix to ccs format");
        }
    }
    //проходимся по столбцам
    for (int i = 0; i < width; ++i) {
        //записываем индекс первого значения столбца в LJ
        LJ.pushBack(LI.getSize() + 1);
        //проходимся по текущему столбцу и записываем ненулевые значения
        for (int j = 0; j < height; ++j) {
            T* item = matrix.getItemPtr(j)->getItemPtr(i);
            if(*item != zeroElement) {
                values.pushBack(*item);
                LI.pushBack(j + 1);
            }
        }
    }
    //записываем размер LI
    LJ.pushBack(LI.getSize() + 1);
}

/*
 * Деструктор CCSMatrix
 * деструктор ничего не принимает
 * деструктор ничего не возвращает
 */
template<typename T>
CCSMatrix<T>::~CCSMatrix() = default;

/*
 * Метод clear
 * метод ничего не принимает
 * метод ничего не возвращает
 */
template<typename T>
void CCSMatrix<T>::clear() {
    values.clear();
    LI.clear();
    LJ.clear();
}

/*
 * Метод printAsCCS
 * printer - функция вывода элемента типа T
 * метод ничего не возвращает
 */
template<typename T>
void CCSMatrix<T>::printAsCCS(void (*printer)(T)) {
    std::cout << "Ccs: " << std::endl;
    std::cout << "values: " << std::endl;
    values.print(printer);
    auto printerInt = [](int i){
        std::cout << i << " ";
    };
    std::cout << "LI: " << std::endl;
    LI.print(printerInt);
    std::cout << "LJ: " << std::endl;
    LJ.print(printerInt);
}

/*
 * Метод printAsMatrix
 * printer - функция вывода элемента типа T
 * zeroElement - значение нулевого элемента
 * метод ничего не возвращает
 */
template<typename T>
void CCSMatrix<T>::printAsMatrix(void (*printer)(T), T zeroElement) {
    std::cout << "Matrix: " << std::endl;

    //считаем ширину и высоту матрицы
    int width = LJ.getSize() - 1;
    int height = 0;
    for (int i = 0; i < LI.getSize(); ++i) {
        if(height < *LI.getItemPtr(i)){
            height = *LI.getItemPtr(i);
        }
    }

    //проходимся по строкам и столбцвм
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            //ищем в LI номер текущей строки в диапазоне индексов из LJ и выводим элемент
            //из values по индексу LI
            bool isZero = true;
            for (int k = *LJ.getItemPtr(j) - 1; k < *LJ.getItemPtr(j + 1) - 1; ++k) {
                if(*LI.getItemPtr(k) == i + 1){
                    isZero = false;
                    printer(*values.getItemPtr(k));
                }
            }
            //если не нашлось значения, выводим нулевой элемент
            if(isZero){
                printer(zeroElement);
            }

        }
        std::cout << std::endl;
    }
}

/*
 * Метод getEvenIndexElements
 * printer - функция вывода элемента типа T
 * метод ничего не возвращает
 */
template<typename T>
void CCSMatrix<T>::getEvenIndexElements(void (*printer)(T)) {
    std::cout << "Elements: " << std::endl;
    //проходим по списку значений и вычисляем координаты значения
    for (int i = 0; i < values.getSize(); ++i) {
        int y = *LI.getItemPtr(i);
        int x;
        //доходим во максимального элемента LJ,
        //в котором записано значение меньше индекса значения
        for (int j = 0; j < LJ.getSize(); ++j) {
            if(*LJ.getItemPtr(j) > i + 1)
                break;
                x = j + 1;
        }
        //вывод элементов с четной суммой индексов
        if((x + y) % 2 == 0) {
            std::cout << x << ", " << y << ": ";
            printer(*values.getItemPtr(i));
            std::cout << std::endl;
        }
    }
}
