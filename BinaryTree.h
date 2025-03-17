#pragma once

#include <iostream>
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
//    void printBranchesWithMaxChilds(void (*printer)(T));

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

    while (queue.getSize() - queueIndex != 0) {
        int levelSize = queue.getSize() - queueIndex;
        for (int i = 0; i < levelSize; ++i) {
            BinaryTree* item = queue.getItemPtr(queueIndex);
            queueIndex++;
            printer(item->_data);

            if (item->_left != nullptr) {
                queue.pushBack(*(item->_left));
            }
            if (item->_right != nullptr) {
                queue.pushBack(*(item->_right));
            }
        }
        std::cout << std::endl;
    }
}



