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
    cout << this << endl;
    for (int i = _children.getSize() - 1; i >= 0; --i) {
        try{
            _children.getItemPtr(i) == nullptr;
            cout << _children.getItemPtr(i);
            delete _children.getItemPtr(i);
            cout << "+" << endl;
        }catch(...) {
            cout << "-" << endl;
        }
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

//template<typename T>
//void NTree<T>::print(void (*printer)(T, bool)) {
//    // добавляем в очередь корень
//    LinkedList<NTree<T>> queue = LinkedList<NTree<T>>();
//
//    queue.pushBack(*this, false);
//    //костыль для работы со списком как с очередью (push = pushBack, pop = queueIndex++)
//    int queueIndex = 0;
//    int levelCount = 0;
//    //глубина дерева
//    int deep = getDeep(0);
//    //число символов гна элемент
//    int cellsForElement = pow(2, deep);
//    //проходим по очереди не дойдем до последнего уровня
//    while (levelCount < deep) {
//        //количество элементов в слое
//        int levelSize = queue.getSize() - queueIndex;
//        levelCount ++;
//        //проходим по слою
//        for (int i = 0; i < levelSize; ++i) {
//            //выводим текущий элемент либо пробел, если он пустой
//            BinaryTree* item = queue.getItemPtr(queueIndex);
//            queueIndex++;
//            printer(item->_data, queue.isEmpty(queueIndex - 1));
//
//            //вывод пробелов для красивого отображения слоя
//            for (int j = 0; j < cellsForElement - 1; ++j) {
//                std::cout << " ";
//            }
//
//            //добавляем дочерние узлы или пустые узлы в очередь, если текущий узел пустой
//            if (item->_left != nullptr) {
//                queue.pushBack(*(item->_left), false);
//            }
//            else{
//                queue.pushBack(_data, true);
//            }
//            if (item->_right != nullptr) {
//                queue.pushBack(*(item->_right), false);
//            }
//            else{
//                queue.pushBack(_data, true);
//            }
//        }
//        //уменьшаем количество символов для элементов следующего слоя
//        cellsForElement /= 2;
//        std::cout << std::endl;
//}
