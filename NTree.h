#pragma once

#include <iostream>
#include <math.h>
#include "LinkedList.h"

using namespace std;

//Дано N-дерево. Найти все поддеревья, листья которых находятся в заданном диапазоне высот от корня поддерева.

/*
 * NTree - n-дерево
 * _data - значение узла
 * _n - количество потомков
 * _children - список потомков
 * getDeep - метод получения глубины дерева
 * getMinDeep - метод получения минимального уровня листа
 * addChild - метод добавления потомка
 * getChildren - метод получения списка потомков
 * print - метод вывода дерева в консоль
 * printSubTreesInRange - метод вывода поддеревьев, с дочерними узлами в нужном диапазоне
 */
template<typename T>
class NTree {

private:
    T _data;
    int _n;
    LinkedList<NTree<T>*> _children;

    int getDeep(int curDeep);
    int getMinDeep(int curDeep);

public:
    NTree(T data, int n);

    NTree() = default;

    ~NTree();

    void addChild(T child, bool empty);

    LinkedList<NTree<T>*> getChildren();

    void print(void (*printer)(T, bool));

    void printSubTreesInRange(void (*printer)(T, bool), int minLevel, int maxLevel);

};

/*
 * Конструктор NTree
 * data - значение узла
 * n - количество потомков
 */
template<typename T>
NTree<T>::NTree(T data, int n) {
    _data = data;
    _n = n;
}

/*
 * Деструктор NTree
 *
 */
template<typename T>
NTree<T>::~NTree() {
    for (int i = _children.getSize() - 1; i >= 0; --i) {
        try{
            auto temp = _children.getItemPtr(i);
            temp = nullptr;
            delete temp;
        }catch(...) {}
    }
}

/*
 * Метод addChild
 * child - значение нового узла
 * empty - считать ли новый узел пустым
 * метод ничего не возвращает
 */
template<typename T>
void NTree<T>::addChild(T child, bool empty) {
    if(_children.getSize() >= _n){
        throw string ("can not add child");
    }
    NTree<T>* newChild = new NTree<T>(child, _n);
    _children.pushBack(newChild, empty);
}

/*
 * Метод getChildren
 * метод ничего не принимает
 * возвращает список указателей на дочерние узлы
 */
template<typename T>
LinkedList<NTree<T> *> NTree<T>::getChildren() {
    return _children;
}

/*
 * Метод getDeep
 * curDeep - текущая глубина
 * возвращает глубину дерева + текущая глубина
 */
template<typename T>
int NTree<T>::getDeep(int curDeep) {
    //выход из рекурсии на листе
    bool fl = true;
    for (int i = 0; i < _children.getSize(); ++i) {
        if(!_children.isEmpty(i)){
            fl = false;
        }
    }
    if(fl){
        return curDeep + 1;
    }

    //возвращаем самое большое значение функции от дочерних узлов
    int maxDeep = 0;
    for (int i = 0; i < _children.getSize(); ++i) {
        auto a = *_children.getItemPtr(i);
        int tmpDeep = a->getDeep(curDeep + 1);
        if(tmpDeep > maxDeep){
            maxDeep = tmpDeep;
        }
    }
    return maxDeep;
}

/*
 * Метод print
 * printer - функция вывода типа T в консоль
 * метод ничего не возвращает
 */
template<typename T>
void NTree<T>::print(void (*printer)(T, bool)) {
    // добавляем в очередь корень
    LinkedList<NTree<T>> queue = LinkedList<NTree<T>>();

    queue.pushBack(*this, false);
    //костыль для работы со списком как с очередью (push = pushBack, pop = queueIndex++)
    int queueIndex = 0;
    int levelCount = 0;
    //глубина дерева
    int deep = getDeep(0);
    //число символов гна элемент
    int cellsForElement = pow(_n, deep - 1);
    //проходим по очереди пока не дойдем до последнего уровня
    while (levelCount < deep) {
        //количество элементов в слое
        int levelSize = queue.getSize() - queueIndex;
        levelCount ++;
        //проходим по слою
        for (int i = 0; i < levelSize; ++i) {
            //выводим текущий элемент либо пробел, если он пустой
            NTree* item = queue.getItemPtr(queueIndex);
            bool itemEpmty = queue.isEmpty(queueIndex);
            queueIndex++;
            for (int j = 0; j < cellsForElement; ++j) {
                std::cout << " ";
            }
            printer(item->_data, itemEpmty);

            //вывод пробелов для красивого отображения слоя
            for (int j = 0; j < cellsForElement - 1; ++j) {
                std::cout << " ";
            }

            for (int j = 0; j < item->_children.getSize(); ++j) {
                if (*(item->_children.getItemPtr(j)) != nullptr && !itemEpmty) {
                    queue.pushBack(*(*(item->_children.getItemPtr(j))), item->_children.isEmpty(j));
                }
                else{
                    queue.pushBack(*this, true);
                }
            }
            for (int j = 0; j < _n - item->_children.getSize(); ++j) {
                queue.pushBack(*this, true);
            }
        }
        //уменьшаем количество символов для элементов следующего слоя
        cellsForElement /= _n;
        std::cout << std::endl;
    }
}

/*
 * Метод getMinDeep
 * curDeep - текущая глубина
 * возвращает минимальный уровень, на котором есть лист + текущая глубина
 */
template<typename T>
int NTree<T>::getMinDeep(int curDeep) {
    //выход из рекурсии на листе
    bool fl = true;
    for (int i = 0; i < _children.getSize(); ++i) {
        if(!_children.isEmpty(i)){
            fl = false;
        }
    }
    if(fl){
        return curDeep + 1;
    }

    //возвращаем самое большое значение функции от дочерних узлов
    int minDeep = getDeep(curDeep);
    for (int i = 0; i < _children.getSize(); ++i) {
        NTree<T>* child = *_children.getItemPtr(i);
        if(!_children.isEmpty(i)) {
            int tmpDeep = child->getMinDeep(curDeep + 1);
            if (tmpDeep < minDeep) {
                minDeep = tmpDeep;
            }
        }
    }
    return minDeep;
}

/*
 * Метод printSubTreesInRange
 * printer - функция вывода типа T в консоль
 * minLevel - нижняя граница диапазона
 * maxLevel - верхняя граница диапазона
 * метод ничего не возвращает
 */
template<typename T>
void NTree<T>::printSubTreesInRange(void (*printer)(T, bool), int minLevel, int maxLevel) {
    //получаем диапазон листьев текущего дерева
    //и выводим, если он не выходит за пределы нужного диапазона
    int min = getMinDeep(0);
    int max = getDeep(0);
    bool fl = false;
    for (int i = 0; i < _children.getSize(); ++i) {
        if(!_children.isEmpty(i)){
            fl = true;
        }
    }
    if(min >= minLevel && max <= maxLevel && fl){
        print(printer);
    }
    //рекурсивно применяем метод к дочерним узлам, корректируя диапазон

    for (int i = 0; i < _children.getSize(); ++i) {
        if(!_children.isEmpty(i)){
            (*_children.getItemPtr(i))->printSubTreesInRange(printer, minLevel - 1, maxLevel - 1);
        }
    }
}