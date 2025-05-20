#pragma once

#include <iostream>

/*
 * item - структура для хранения элемента списка
 * data - элемент списка
 * next - указатель на следующий элемент
 * */
template<typename T>
struct item {
    T data;
    item *next;

    item(T d, item *n);
};

/*
 * LinkedList - класс списка
 * first - указатель на первый элемент
 * size - размер списка
 * pushBack - метод вставки в конец списка
 * pushTo - метод вставки между элементами
 * remove - метод удаления элемента
 * getItemPtr - метод получения указателя на элемент
 * getSize - метод получения размера
 * */
template<typename T>
class LinkedList {

private:
    item<T> *first;
    int size;

public:
    LinkedList();
    ~LinkedList();

    void pushBack(T data);
    void pushTo(int index, T data);
    void remove(int index);
    T *getItemPtr(int index);
    int getSize();

};

/*
 * конструктор item
 * d - значение элемента
 * n - указатель на следующий элемент
 */
template<typename T>
item<T>::item(T d, item *n) {
    data = d;
    next = n;
}


/*
 * конструктор
 * */
template<typename T>
LinkedList<T>::LinkedList() {
    first = nullptr;
    size = 0;
}

/*
 * деструктор
 * */
template<typename T>
LinkedList<T>::~LinkedList() {
    //если список не пуст, проходимся по списку и освобождаем память
    if (first == nullptr)
        return;
    item<T> *cur = first;
    while (cur != nullptr) {
        item<T> *next = cur->next;
        delete cur;
        cur = next;
    }
}

/*
 * pushBack - метод вставки в конец
 * data - значение для вставки
 * метод ничего не возвращает
 * */
template<typename T>
void LinkedList<T>::pushBack(T data) {
    //если список пуст, записываем в первый элемент
    if (first == nullptr) {
        first = new item<T>(data, nullptr);
        size++;
        return;
    }
    //если список не пуст, получаем указатель
    //на последний элемент и добавляем новый
    item<T> *cur = first;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = new item<T>(data, nullptr);
    size++;
}

/*
 * pushTo - метод вставки по индексу
 * index - индекс для вставки
 * data - значение для вставки
 * метод ничего не возвращает
 * */
template<typename T>
void LinkedList<T>::pushTo(int index, T data) {
    //проверяем корректность индекса
    if (index < 0 || index > size)
        return;

    //вставляем элемент по индексу с изменением указателей в соседних элементах
    if (index == 0) {
        first = new item<T>(data, first);
        size++;
    } else {
        item<T> *prev = first;
        for (int i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        prev->next = new item<T>(data, prev->next);
        size++;
    }
}

/*
 * remove - метод удаления по индексу
 * index - индекс для удаления
 * метод ничего не возвращает
 * */
template<typename T>
void LinkedList<T>::remove(int index) {
    //проверяем корректность индекса
    if (index < 0 || index >= size)
        return;

    //получаем указатель для удаления и убираем указатели на него
    item<T> *toDelete;
    if (index == 0) {
        toDelete = first;
        first = first->next;
    } else {
        item<T> *prev = first;
        for (int i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        toDelete = prev->next;
        prev->next = toDelete->next;
    }
    //освобождаем память
    delete toDelete;
    size--;
}

/*
 * getItemPtr - метод получения указатели на элемент по индексу
 * index - индекс для получения элемента
 * возвращает указатель на элемент
 * */
template<typename T>
T *LinkedList<T>::getItemPtr(int index) {
    //проверяем корректность индекса
    if (index < 0)
        return nullptr;
    //доходим до нужного элемента и возвращаем указатель
    item<T> *cur = first;
    for (int i = 0; i < index; ++i) {
        if (cur == nullptr)
            return nullptr;
        cur = cur->next;
    }
    return &cur->data;
}

/*
 * getSize - метод получения размера списка
 * метод ничего не принимает
 * возвращает размер массива
 * */
template<typename T>
int LinkedList<T>::getSize() {
    return size;
}