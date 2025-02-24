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
    item* next;
    item(T d, item* n);
};


/*
 * Класс LinkedList - список
 * first - ссылка на первый элемент или nullptr
 * pushBack - метод для вставки элемента в конец списка
 * print - метод для вывода элементов списка в консоль
 */
template<typename T>
class LinkedList {

private:
    item<T>* first;

public:
    LinkedList();
    ~LinkedList();
    void pushBack(T data);
    void print(void (*printer)(T item));
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
 * Конструктор item
 * не принимает параметры
 */
template<typename T>
LinkedList<T>::LinkedList() {
    // при создании список пустой
    first = nullptr;
}

/*
 * Деструктор item
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
    item<T>* cur = first;
    while (cur != nullptr){
        item<T>* next = cur->next;
        delete cur;
        cur = next;
    }
}

/*
 * метод pushBack
 * data - данные для добавления в конец списка
 */
template<typename T>
void LinkedList<T>::pushBack(T data) {
    //если список пустой, записываем первый элемент
    if (first == nullptr) {
        first = new item<T>(data, nullptr);
        return;
    }
    //если список не пустой, доходим до последнего элемента и добавляем новый
    item<T>* cur = first;
    while (cur->next != nullptr){
        cur = cur-> next;
    }
    cur->next = new item<T>(data, nullptr);
}

/*
 * метод print
 * printer - функция вывода типа T в консоль
 */
template<typename T>
void LinkedList<T>::print(void (*printer)(T)) {
    //если список пустой, выводим сообщение
    if (first == nullptr) {
        std::cout << "list is empty" << std::endl;
        return;
    }
    //выводим список
    std::cout << "list:" << std::endl;
    item<T>* cur = first;
    while (cur != nullptr){
        //вывод элемента типа T
        printer(cur->data);
        std::cout << std::endl;
        cur = cur->next;
    }
}
