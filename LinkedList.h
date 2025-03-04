#pragma once

#include <iostream>


/*
 * Структура item - ячейка списка
 * data - данные элемента списка
 * next - ссылка на следующий элемент или nullptr
 */
template<typename T>
struct item {
    T data;
    item *next;

    item(T d, item *n);
};


/*
 * Класс LinkedList - связанный список
 * first - ссылка на первый элемент или nullptr
 * pushBack - метод для вставки элемента в конец списка
 * pushBack - метод для получения ссылки на элемент по индексу
 * clear - очистка списка
 * print - метод для вывода элементов списка в консоль
 * iterate - метод для получения всех элементов списка и их индексов
 */
template<typename T>
class LinkedList {

private:
    item<T> *first;

public:
    LinkedList();

    ~LinkedList();

    void pushBack(T data);

    T *getItemPtr(int index);

    void clear();

    void print(void (*printer)(T item));

    void iterate(void (*handler)(int index, T item));

};

/*
 * Конструктор item
 * d - данные элемента списка
 * n - ссылка на следующий элемент или nullptr
 */
template<typename T>
item<T>::item(T d, item *n) {
    data = d;
    next = n;
}

/*
 * Конструктор LinkedList
 * не принимает параметры
 */
template<typename T>
LinkedList<T>::LinkedList() {
    // при создании список пустой
    first = nullptr;
}

/*
 * Деструктор LinkedList
 * не принимает параметры
 */
template<typename T>
LinkedList<T>::~LinkedList() {
    //освобождение памяти списка
    //если список пустой
    if (first == nullptr) {
        return;
    }
    //если список не пустой, проходим по всем элементам и освобождаем память
    item<T> *cur = first;
    while (cur != nullptr) {
        item<T> *next = cur->next;
        delete cur;
        cur = next;
    }
}

/*
 * метод pushBack
 * data - данные для добавления в конец списка
 * функция ничего не возвращает
 */
template<typename T>
void LinkedList<T>::pushBack(T data) {
    //если список пустой, записываем первый элемент
    if (first == nullptr) {
        first = new item<T>(data, nullptr);
        return;
    }
    //если список не пустой, доходим до последнего элемента и добавляем новый
    item<T> *cur = first;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = new item<T>(data, nullptr);
}

/*
 * метод clear
 * функция ничего не принимает
 * функция ничего не возвращает
 */
template<typename T>
void LinkedList<T>::clear() {
    //если список пустой
    if (first == nullptr) {
        return;
    }
    //если список не пустой, проходим по всем элементам и освобождаем память
    item<T> *cur = first;
    while (cur != nullptr) {
        item<T> *next = cur->next;
        delete cur;
        cur = next;
    }
}

/*
 * метод print
 * printer - функция вывода типа T в консоль
 * функция ничего не возвращает
 */
template<typename T>
void LinkedList<T>::print(void (*printer)(T)) {
    //если список пустой, выводим сообщение
    if (first == nullptr) {
        std::cout << "list is empty" << std::endl;
        return;
    }
    //выводим список
    item<T> *cur = first;
    while (cur != nullptr) {
        //вывод элемента типа T
        printer(cur->data);
        std::cout << std::endl;
        cur = cur->next;
    }
}

/*
 * метод iterate
 * handler - функция-обработчик для элементов списка
 * функция ничего не возвращает
 */
template<typename T>
void LinkedList<T>::iterate(void (*handler)(int, T)) {
    //если список пустой, выходим из функции
    if (first == nullptr) {
        return;
    }
    //проходим о списку
    item<T> *cur = first;
    int index = 0;
    while (cur != nullptr) {
        //вызываем обработчик для элемента
        printer(index, cur->data);
        index++;
        cur = cur->next;
    }
}

/*
 * Функция getItemPtr
 * index - индекс элемента, ссылку на который нужно получить
 * функция возвращает ссылку на нужный элемент или nullptr, если такого индекса нет
 */
template<typename T>
T *LinkedList<T>::getItemPtr(int index) {
    //если некорректный индекс
    if (index < 0)
        return nullptr;
    //переходим к нужному элементу
    item<T> *cur = first;
    for (int i = 0; i < index; ++i) {
        //если список закончился
        if (cur == nullptr)
            return nullptr;
        cur = cur->next;
    }
    return &cur->data;
}