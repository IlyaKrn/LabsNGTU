#pragma once

#include <iostream>
#include <math.h>
#include "LinkedList.h"

// Дано бинарное дерево. Найти ветви с мах числом ветвлений.

template<typename T>
class BinaryTree {

private:
    T _data;
    BinaryTree *_right;
    BinaryTree *_left;

public:
    BinaryTree(T data);

    BinaryTree() = default;

    ~BinaryTree();

    void setRightValue(T right);

    void setLeftValue(T left);

    BinaryTree *getRightPtr();

    BinaryTree *getLeftPtr();

    void print(void (*printer)(T));

//    void printBranchesWithMaxChildren(void (*printer)(T));

};

template<typename T>
BinaryTree<T>::BinaryTree(T data) {
    _data = data;
    _left = nullptr;
    _right = nullptr;
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
//    delete _right;
//    delete _left;
}

template<typename T>
void BinaryTree<T>::setLeftValue(T left) {
    if (_left != nullptr)
        delete _left;
    _left = new BinaryTree(left);

}

template<typename T>
void BinaryTree<T>::setRightValue(T right) {
    if (_right != nullptr)
        delete _right;
    _right = new BinaryTree(right);

}

template<typename T>
BinaryTree<T> *BinaryTree<T>::getLeftPtr() {
    return _left;
}

template<typename T>
BinaryTree<T> *BinaryTree<T>::getRightPtr() {
    return _right;
}

template<typename T>
void BinaryTree<T>::print(void (*printer)(T)) {
    LinkedList<BinaryTree<T>> queue = LinkedList<BinaryTree<T>>();

    queue.pushBack(*this);
    int queueIndex = 0;

    int cellsForElement = pow(2, 6);//2 ^ deep of tree
    while (queue.getSize() - queueIndex != 0) {
        int levelSize = queue.getSize() - queueIndex;
        for (int i = 0; i < levelSize; ++i) {
            BinaryTree* item = queue.getItemPtr(queueIndex);
            queueIndex++;
            printer(item->_data);

            for (int j = 0; j < cellsForElement - 1; ++j) {
                std::cout << " ";
            }

            if (item->_left != nullptr) {
                queue.pushBack(*(item->_left));
            }
            if (item->_right != nullptr) {
                queue.pushBack(*(item->_right));
            }
        }
        cellsForElement /= 2;
        std::cout << std::endl;
    }
}


//глубина дерева при выводе в консоль
//реализация алгоритма задачи
//ввод дерева с консоли


