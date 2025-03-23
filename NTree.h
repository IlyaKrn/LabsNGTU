#pragma once

#include <iostream>
#include <math.h>
#include "LinkedList.h"

using namespace std;

//Дано N-дерево. Найти все поддеревья, листья которых находятся в заданном диапазоне высот от корня поддерева.

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

template<typename T>
NTree<T>::NTree(T data, int n) {
    _data = data;
    _n = n;
}

template<typename T>
NTree<T>::~NTree() {
    for (int i = _children.getSize() - 1; i >= 0; --i) {
        try{
            _children.getItemPtr(i) == nullptr;
//            delete _children.getItemPtr(i);
        }catch(...) {}
    }
}

template<typename T>
void NTree<T>::addChild(T child, bool empty) {
    if(_children.getSize() >= _n){
        throw string ("can not add child");
    }
    NTree<T>* newChild = new NTree<T>(child, _n);
    _children.pushBack(newChild, empty);
}

template<typename T>
LinkedList<NTree<T> *> NTree<T>::getChildren() {
    return _children;
}

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

template<typename T>
void NTree<T>::printSubTreesInRange(void (*printer)(T, bool), int minLevel, int maxLevel) {
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

    for (int i = 0; i < _children.getSize(); ++i) {
        if(!_children.isEmpty(i)){
            (*_children.getItemPtr(i))->printSubTreesInRange(printer, minLevel - 1, maxLevel - 1);
        }
    }
}