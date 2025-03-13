#pragma once

#include <iostream>

// Дано бинарное дерево. Найти ветви с мах числом ветвлений.

template<typename T>
class BinaryTree {

private:
    T _data;
    BinaryTree* _right;
    BinaryTree* _left;

public:
    BinaryTree(T data);
    BinaryTree(T data, BinaryTree* right, BinaryTree* left);
    ~BinaryTree();
    void clear();
    void setRight(BinaryTree* right);
    void setLeft(BinaryTree* left);
    void printBranchesWithMaxChilds(void (*printer)(T));

};

template<typename T>
BinaryTree<T>::BinaryTree(T data, BinaryTree *right, BinaryTree *left) {
    _data = data;
    _right = right;
    _left = left;
}

template<typename T>
BinaryTree<T>::BinaryTree(T data) {
    _data = data;
}
