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
 * Класс LinkedList - связанный список
 * first - ссылка на первый элемент или nullptr
 * pushBack - метод для вставки элемента в конец списка
 * clear - очистка списка
 * print - метод для вывода элементов списка в консоль
 * cyclicShiftLeft - метод для циклического сдвига влево на заданное количество элементов
 */
template<typename T>
class LinkedList {

private:
    item<T>* first;

public:
    LinkedList();
    ~LinkedList();
    void pushBack(T data);
    void clear();
    void print(void (*printer)(T item));
    void cyclicShiftLeft(int n);
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
    item<T>* cur = first;
    while (cur->next != nullptr){
        cur = cur-> next;
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
    item<T>* cur = first;
    while (cur != nullptr){
        item<T>* next = cur->next;
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
    item<T>* cur = first;
    while (cur != nullptr){
        //вывод элемента типа T
        printer(cur->data);
        std::cout << std::endl;
        cur = cur->next;
    }
}

/*
 * метод cyclicShiftLeft
 * n - количество элементов, на которое произойдет сдвиг
 * функция ничего не возвращает
 */
template<typename T>
void LinkedList<T>::cyclicShiftLeft(int n) {
    //если список пустой или нет сдвига
    if (first == nullptr || n == 0)
        return;
    //доходим до конца списка и считаем размер по
    //количеству ссылок на следующий элемент + первый
    item<T>* last = first;
    int size = 1;
    while (last->next != nullptr){
        last = last->next;
        size++;
    }
    //связываем первый и последний элементы
    last->next = first;

    //переход к новому последнему элементу
    item<T>* newLast = first;
    for (int i = 0; i < n - 1; ++i) {
        newLast = newLast->next;
    }

    //сдвигаем первый элемент и убираем ссылку из предпоследнего
    first = newLast->next;
    newLast->next = nullptr;
}
