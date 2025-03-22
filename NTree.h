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

public:
    NTree(T data, int n);

    NTree() = default;

    ~NTree();

    void addChild(T child);

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
void NTree<T>::addChild(T child) {
    if(_children.getSize() >= _n){
        throw string ("can not add child");
    }
    NTree<T>* newChild = new NTree<T>(child, _n);
    _children.pushBack(newChild, false);
}

template<typename T>
LinkedList<NTree<T> *> NTree<T>::getChildren() {
    return _children;
}

template<typename T>
int NTree<T>::getDeep(int curDeep) {
    //выход из рекурсии на листе
    if(_children.getSize() == 0){
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
            queueIndex++;
            for (int j = 0; j < cellsForElement; ++j) {
                std::cout << " ";
            }
            printer(item->_data, queue.isEmpty(queueIndex - 1));

            //вывод пробелов для красивого отображения слоя
            for (int j = 0; j < cellsForElement - 1; ++j) {
                std::cout << " ";
            }

            for (int j = 0; j < item->_children.getSize(); ++j) {
                if (*(item->_children.getItemPtr(j)) != nullptr && !queue.isEmpty(queueIndex - 1) ) {
                    queue.pushBack(*(*(item->_children.getItemPtr(j))), false);
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