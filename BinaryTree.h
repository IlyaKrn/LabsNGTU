#pragma once

#include <iostream>
#include <math.h>
#include "LinkedList.h"

// Дано бинарное дерево. Найти ветви с мах числом ветвлений.

/*
 * структура branchingItem - вспомогательная структура для подсчета ветвлений
 * _data - значение элемента для вывода
 * isBranching - есть ли у узла оба дочерних узла
 */
template<typename T>
struct branchingItem{
    T _data;
    bool isBranching;

    branchingItem(T data, bool branching);
    branchingItem();
};

/*
 * BinaryTree - класс бинарного дерева
 * _right - правый дочерний узел дерева
 * _left- левый дочерний узел дерева
 * getDeep - метод получения глубины дерева
 * getBranches - метод получения всех ветвей
 * setRightValue - метод добавления указателя правого узла
 * setLeftValue - метод добавления указателя левого узла
 * getRightPtr - метод получения указателя правого узла
 * getLeftPtr - метод получения указателя левого узла
 * print - метод вывода дерева в консоль
 * printBranchesWithMaxChildren - метод вывода ветвей с максимальным числом ветвлений
 */
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

/*
 * конструктор branchingItem
 * data - значение элемента для вывода
 * branching - есть ли у узла оба дочерних узла
 */
template<typename T>
branchingItem<T>::branchingItem(T data, bool branching) {
    _data = data;
    isBranching = branching;
}

/*
 * конструктор branchingItem
 * конструктор не принимает параметры
 */
template<typename T>
branchingItem<T>::branchingItem() {
    isBranching = false;
}

/*
 * конструктор BinaryTree
 * data - значение элемента для узла
 */
template<typename T>
BinaryTree<T>::BinaryTree(T data) {
    _data = data;
    _left = nullptr;
    _right = nullptr;
}

/*
 * деструктор BinaryTree
 */
template<typename T>
BinaryTree<T>::~BinaryTree() {
    //проверка на уже освобожденную память и освобождение
    try{
        _left = nullptr;
        delete _left;
    }catch(...) {}
    try{
        _right = nullptr;
        delete _right;
    }catch(...) {}
}

/*
 * Метод setLeftValue
 * left - значение левого узла
 * метод ничего не возвращает
 */
template<typename T>
void BinaryTree<T>::setLeftValue(T left) {
    //освобождаем память если узел не пуст
    if (_left != nullptr)
        delete _left;
    _left = new BinaryTree(left);

}

/*
 * Метод setLeftValue
 * right - значение правого узла
 * метод ничего не возвращает
 */

template<typename T>
void BinaryTree<T>::setRightValue(T right) {
    //освобождаем память если узел не пуст
    if (_right != nullptr)
        delete _right;
    _right = new BinaryTree(right);

}

/*
 * Метод getLeftPtr
 * метод ничего не принимает
 * метод возвращает указатель левого узла
 */

template<typename T>
BinaryTree<T> *BinaryTree<T>::getLeftPtr() {
    return _left;
}

/*
 * Метод getRightPtr
 * метод ничего не принимает
 * метод возвращает указатель правого узла
 */

template<typename T>
BinaryTree<T> *BinaryTree<T>::getRightPtr() {
    return _right;
}

/*
 * Метод getDeep
 * curDeep - текущая глубина рекурсии
 * метод возвращает максимальную длину ветви
 */

template<typename T>
int BinaryTree<T>::getDeep(int curDeep) {
    //выход из рекурсии на листе
    if(_left == nullptr && _right == nullptr){
        return curDeep + 1;
    }

    //возвращаем самое большое значение функции от дочерних узлов
    int leftDeep = 0;
    int rightDeep = 0;
    if(_left != nullptr){
        leftDeep = _left->getDeep(curDeep + 1);
    }
    if(_right != nullptr){
        rightDeep = _right->getDeep(curDeep + 1);
    }

    return (leftDeep > rightDeep ? leftDeep : rightDeep);
}

/*
 * Метод print
 * printer - функция вывода типа T в консоль
 * метод ничего не возвращает
 */
template<typename T>
void BinaryTree<T>::print(void (*printer)(T, bool)) {
    // добавляем в очередь корень
    LinkedList<BinaryTree<T>> queue = LinkedList<BinaryTree<T>>();

    queue.pushBack(*this, false);
    //костыль для работы со списком как с очередью (push = pushBack, pop = queueIndex++)
    int queueIndex = 0;
    int levelCount = 0;
    //глубина дерева
    int deep = getDeep(0);
    //число символов гна элемент
    int cellsForElement = pow(2, deep);
    //проходим по очереди не дойдем до последнего уровня
    while (levelCount < deep) {
        //количество элементов в слое
        int levelSize = queue.getSize() - queueIndex;
        levelCount ++;
        //проходим по слою
        for (int i = 0; i < levelSize; ++i) {
            //выводим текущий элемент либо пробел, если он пустой
            BinaryTree* item = queue.getItemPtr(queueIndex);
            queueIndex++;
            printer(item->_data, queue.isEmpty(queueIndex - 1));

            //вывод пробелов для красивого отображения слоя
            for (int j = 0; j < cellsForElement - 1; ++j) {
                std::cout << " ";
            }

            //добавляем дочерние узлы или пустые узлы в очередь, если текущий узел пустой
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
        //уменьшаем количество символов для элементов следующего слоя
        cellsForElement /= 2;
        std::cout << std::endl;
    }
}

/*
 * Метод getBranches
 * currentStack - текущая ветвь
 * allBranches - список всех ветвей
 * метод ничего не возвращает
 */
template<typename T>
void BinaryTree<T>::getBranches(LinkedList<BinaryTree> currentStack, LinkedList<LinkedList<branchingItem<T>>> *allBranches) {
    //текущий элемент ветви
    BinaryTree<T> cur = *(currentStack.getItemPtr(currentStack.getSize() - 1));
    //выход из рекурсии если текущий - лист
    if(cur._left == nullptr && cur._right == nullptr){
        //формирование новой ветки и добавление в список
        LinkedList<branchingItem<T>> newBranch = LinkedList<branchingItem<T>>();
        for (int i = 0; i < currentStack.getSize(); ++i) {
            BinaryTree<T> currentItem = *(currentStack.getItemPtr(i));
            //элемент ветви с параметром ветвления
            branchingItem<T> it = branchingItem<T>(currentItem._data, (currentItem._left != nullptr && currentItem._right != nullptr));
            newBranch.pushBack(it, false);
        }
        allBranches->pushBack(newBranch, false);
        return;
    }
    //добавление дочерних узлов и продолжение рекурсии
    if(cur._left != nullptr){
        //копирование ветви + следующий элемент
        LinkedList<BinaryTree> nextStack = LinkedList<BinaryTree>();
        for (int i = 0; i < currentStack.getSize(); ++i) {
            nextStack.pushBack(*(currentStack.getItemPtr(i)), false);
        }
        nextStack.pushBack(*cur._left, false);
        //заполнение списка ветвей
        getBranches(nextStack, allBranches);
    }
    if(cur._right != nullptr){
        //копирование ветви + следующий элемент
        LinkedList<BinaryTree> nextStack = LinkedList<BinaryTree>();
        for (int i = 0; i < currentStack.getSize(); ++i) {
            nextStack.pushBack(*(currentStack.getItemPtr(i)), false);
        }
        nextStack.pushBack(*cur._right, false);
        //заполнение списка ветвей
        getBranches(nextStack, allBranches);
    }
}

/*
 * Метод printBranchesWithMaxChildren
 * printer - функция вывода типа T в консоль
 * метод ничего не возвращает
 */
template<typename T>
void BinaryTree<T>::printBranchesWithMaxChildren(void (*printer)(T, bool)) {

    //получение списка ветвей
    LinkedList<LinkedList<branchingItem<T>>> all = LinkedList<LinkedList<branchingItem<T>>>();
    LinkedList<BinaryTree> current = LinkedList<BinaryTree>();

    current.pushBack(*this, false);

    getBranches(current, &all);
    //получение максимального количества ветвлений
    int maxCount = 0;
    for (int i = 0; i < all.getSize(); ++i) {
        int branching = 0;
        //не учитываем корень, лист, предпоследний элемент
        for (int j = 1; j < all.getItemPtr(i)->getSize() - 2; ++j) {
            if(all.getItemPtr(i)->getItemPtr(j)->isBranching){
                branching++;
            }
        }
        if(maxCount < branching){
            maxCount = branching;
        }
    }
    //вывод нужных ветвей
    for (int i = 0; i < all.getSize(); ++i) {
        //считаем ветвления
        int branching = 0;
        for (int j = 1; j < all.getItemPtr(i)->getSize() - 2; ++j) {
            if(all.getItemPtr(i)->getItemPtr(j)->isBranching){
                branching++;
            }
        }
        //если это максимальное число ветвлений, выводим ветвь
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


