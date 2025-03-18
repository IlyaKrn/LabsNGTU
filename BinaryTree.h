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

    int getDeep(int curDeep);

    int getBranches(LinkedList<BinaryTree> currentStack, LinkedList<LinkedList<T>> *allBranches);

public:
    BinaryTree(T data);

    BinaryTree() = default;

    ~BinaryTree();

    void setRightValue(T right);

    void setLeftValue(T left);

    BinaryTree *getRightPtr();

    BinaryTree *getLeftPtr();

    void print(void (*printer)(T, bool));

    void printBranchesWithMaxChildren(void (*printer)(T, bool));

};

template<typename T>
BinaryTree<T>::BinaryTree(T data) {
    _data = data;
    _left = nullptr;
    _right = nullptr;
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    try{
        _left = nullptr;
        delete _left;
    }catch(...) {}
    try{
        _right = nullptr;
        delete _right;
    }catch(...) {}
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
int BinaryTree<T>::getDeep(int curDeep) {
    if(_left == nullptr && _right == nullptr){
        return curDeep + 1;
    }

    int leftDeep = 0;
    int rightDeep = 0;
    if(_left != nullptr){
        leftDeep = _left->getDeep(curDeep + 1);
    }
    if(_left != nullptr){
        rightDeep = _right->getDeep(curDeep + 1);
    }

    return (leftDeep > rightDeep ? leftDeep : rightDeep);
}

template<typename T>
void BinaryTree<T>::print(void (*printer)(T, bool)) {
    LinkedList<BinaryTree<T>> queue = LinkedList<BinaryTree<T>>();

    queue.pushBack(*this, false);
    int queueIndex = 0;
    int levelCount = 0;
    int deep = getDeep(0);
    int cellsForElement = pow(2, deep);
    while (levelCount < deep) {
        int levelSize = queue.getSize() - queueIndex;
        levelCount ++;
        for (int i = 0; i < levelSize; ++i) {
            BinaryTree* item = queue.getItemPtr(queueIndex);
            queueIndex++;
            printer(item->_data, queue.isEmpty(queueIndex - 1));

            for (int j = 0; j < cellsForElement - 1; ++j) {
                std::cout << " ";
            }

            if (item->_left != nullptr) {
                queue.pushBack(*(item->_left), false);
            }
            else{
                queue.pushBack(_data, true);
            }
            if (item->_right != nullptr) {
                queue.pushBack(*(item->_right), false);
            }
            else{
                queue.pushBack(_data, true);
            }
        }
        cellsForElement /= 2;
        std::cout << std::endl;
    }
}

template<typename T>
int BinaryTree<T>::getBranches(LinkedList<BinaryTree> currentStack, LinkedList<LinkedList<T>> *allBranches) {
    BinaryTree<T> cur = *(currentStack.getItemPtr(currentStack.getSize() - 1));
    if(cur._left == nullptr && cur._right == nullptr){
        LinkedList<T> newBranch = LinkedList<T>();
        for (int i = 0; i < currentStack.getSize(); ++i) {
            newBranch.pushBack(currentStack.getItemPtr(i)->_data, false);
        }
        allBranches->pushBack(newBranch, false);
        return 0;
    }
    if(cur._left != nullptr){
        LinkedList<BinaryTree> nextStack = LinkedList<BinaryTree>();
        for (int i = 0; i < currentStack.getSize(); ++i) {
            nextStack.pushBack(*(currentStack.getItemPtr(i)), false);
        }
        nextStack.pushBack(*cur._left, false);
        getBranches(nextStack, allBranches);
    }
    if(cur._right != nullptr){
        LinkedList<BinaryTree> nextStack = LinkedList<BinaryTree>();
        for (int i = 0; i < currentStack.getSize(); ++i) {
            nextStack.pushBack(*(currentStack.getItemPtr(i)), false);
        }
        nextStack.pushBack(*cur._right, false);
        getBranches(nextStack, allBranches);
    }
    return 0;
}

template<typename T>
void BinaryTree<T>::printBranchesWithMaxChildren(void (*printer)(T, bool)) {

    LinkedList<LinkedList<T>> all = LinkedList<LinkedList<T>>();
    LinkedList<BinaryTree> current = LinkedList<BinaryTree>();

    current.pushBack(*this, false);

    getBranches(current, &all);
    int maxCount = 0;
    for (int i = 0; i < all.getSize(); ++i) {
        all.getItemPtr(i)->print(printer);
    }

}


//ввод дерева с консоли
//комментарии


