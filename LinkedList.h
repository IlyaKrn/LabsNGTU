#pragma once

#include <iostream>

template<typename T>
struct item {
    T data;
    item *next;

    item(T d, item *n);
};

template<typename T>
class LinkedList {

private:
    item<T> *first;
    int size;

public:
    LinkedList();
    ~LinkedList();

    void pushBack(T data);
    T *getItemPtr(int index);
    int getSize();

};

template<typename T>
item<T>::item(T d, item *n) {
    data = d;
    next = n;
}

template<typename T>
LinkedList<T>::LinkedList() {
    first = nullptr;
    size = 0;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    if (first == nullptr)
        return;
    item<T> *cur = first;
    while (cur != nullptr) {
        item<T> *next = cur->next;
        delete cur;
        cur = next;
    }
}

template<typename T>
void LinkedList<T>::pushBack(T data) {
    if (first == nullptr) {
        first = new item<T>(data, nullptr);
        size++;
        return;
    }
    item<T> *cur = first;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = new item<T>(data, nullptr);
    size++;
}

template<typename T>
T *LinkedList<T>::getItemPtr(int index) {
    if (index < 0)
        return nullptr;
    item<T> *cur = first;
    for (int i = 0; i < index; ++i) {
        if (cur == nullptr)
            return nullptr;
        cur = cur->next;
    }
    return &cur->data;
}

template<typename T>
int LinkedList<T>::getSize() {
    return size;
}