#pragma once

#include <iostream>
#include <math.h>
#include "LinkedList.h"

// Дано бинарное дерево. Найти ветви с мах числом ветвлений.

template<typename T>
struct branchingItem{
    T _data;
    bool isBranching;

    branchingItem(T data, bool branching);
    branchingItem();
};


template<typename T>
class BinaryTree {

private:
    T _data;
    BinaryTree *_right;
    BinaryTree *_left;

    int getDeep(int curDeep);

    void getBranches(LinkedList<BinaryTree> currentStack, LinkedList<LinkedList<branchingItem<T>>> *allBranches);

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
branchingItem<T>::branchingItem(T data, bool branching) {
    _data = data;
    isBranching = branching;
}

template<typename T>
branchingItem<T>::branchingItem() {
    isBranching = false;
}

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
void BinaryTree<T>::getBranches(LinkedList<BinaryTree> currentStack, LinkedList<LinkedList<branchingItem<T>>> *allBranches) {
    BinaryTree<T> cur = *(currentStack.getItemPtr(currentStack.getSize() - 1));
    if(cur._left == nullptr && cur._right == nullptr){
        LinkedList<branchingItem<T>> newBranch = LinkedList<branchingItem<T>>();
        for (int i = 0; i < currentStack.getSize(); ++i) {
            BinaryTree<T> currentItem = *(currentStack.getItemPtr(i));
            branchingItem<T> it = branchingItem<T>(currentItem._data, (currentItem._left != nullptr && currentItem._right != nullptr));
            newBranch.pushBack(it, false);
        }
        allBranches->pushBack(newBranch, false);
        return;
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
}

template<typename T>
void BinaryTree<T>::printBranchesWithMaxChildren(void (*printer)(T, bool)) {

    LinkedList<LinkedList<branchingItem<T>>> all = LinkedList<LinkedList<branchingItem<T>>>();
    LinkedList<BinaryTree> current = LinkedList<BinaryTree>();

    current.pushBack(*this, false);

    getBranches(current, &all);
    int maxCount = 0;
    for (int i = 0; i < all.getSize(); ++i) {
        int branching = 0;
        for (int j = 1; j < all.getItemPtr(i)->getSize() - 2; ++j) {
            if(all.getItemPtr(i)->getItemPtr(j)->isBranching){
                branching++;
            }
        }
        if(maxCount < branching){
            maxCount = branching;
        }
    }
    for (int i = 0; i < all.getSize(); ++i) {
        int branching = 0;
        for (int j = 1; j < all.getItemPtr(i)->getSize() - 2; ++j) {
            if(all.getItemPtr(i)->getItemPtr(j)->isBranching){
                branching++;
            }
        }
        if(branching == maxCount){
            std::cout << branching << ": ";
            for (int j = 0; j < all.getItemPtr(i)->getSize(); ++j) {
                printer(all.getItemPtr(i)->getItemPtr(j)->_data, false);
                std::cout << (j != all.getItemPtr(i)->getSize() - 1 ? "-" : "");
            }
            std::cout << std::endl;
        }
    }

}


//ввод дерева с консоли
//комментарии


