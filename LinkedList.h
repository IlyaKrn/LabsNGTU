#pragma once

#include <iostream>


/*
 * Структура item - ячейка списка
 * data - данные элемента списка
 * next - ссылка на следующий элемент или nullptr
 * isEmpty - нужно ли считать ячейку пустой
 */
template<typename T>
struct item {
    T data;
    bool isEmpty;
    item *next;

    item(T d, item *n, bool empty);
};


/*
 * Класс LinkedList - связанный список
 * first - ссылка на первый элемент или nullptr
 * size - размер списка
 * pushBack - метод для вставки элемента в конец списка
 * getItemPtr - метод для получения ссылки на элемент по индексу
 * isEmpty - метод проверки элемента на необходимость считать его пустым
 * clear - очистка списка
 * print - метод для вывода элементов списка в консоль
 * iterate - метод для получения всех элементов списка и их индексов
 * getSize - метод получения размера списка
 */
template<typename T>
class LinkedList {

private:
    item<T> *first;
    int size;

public:
    LinkedList();

    ~LinkedList();

    void pushBack(T data, bool empty);

    T *getItemPtr(int index);

    bool isEmpty(int index);

    void clear();

    void print(void (*printer)(T item));

    void iterate(void (*handler)(int index, T item));

    int getSize();

};

/*
 * Конструктор item
 * d - данные элемента списка
 * n - ссылка на следующий элемент или nullptr
 * empty - считать ли элемент пустым
 */
template<typename T>
item<T>::item(T d, item *n, bool empty) {
    data = d;
    next = n;
    isEmpty = empty;
}

/*
 * Конструктор LinkedList
 * не принимает параметры
 */
template<typename T>
LinkedList<T>::LinkedList() {
    // при создании список пустой
    first = nullptr;
    size = 0;
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
        //проверка, нужно ли освобождать память
        //у вложенного списка.
        //если память доступна, то удаляем
        //если ошибка доступа, то нет
        try{
            cur = nullptr;
        }catch(...) {
            continue;
        }
        delete cur;
        cur = next;
    }
}

/*
 * метод pushBack
 * data - данные для добавления в конец списка
 * empty - считать ли элемент пустым
 * метод ничего не возвращает
 */
template<typename T>
void LinkedList<T>::pushBack(T data, bool empty) {
    //если список пустой, записываем первый элемент
    if (first == nullptr) {
        first = new item<T>(data, nullptr, empty);
        size++;
        return;
    }
    //если список не пустой, доходим до последнего элемента и добавляем новый
    item<T> *cur = first;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = new item<T>(data, nullptr, empty);
    size++;
}

/*
 * Метод clear
 * метод ничего не принимает
 * метод ничего не возвращает
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
    size = 0;
}

/*
 * Метод print
 * printer - функция вывода типа T в консоль
 * метод ничего не возвращает
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
        cur = cur->next;
    }
    std::cout << std::endl;
}

/*
 * Метод iterate
 * handler - функция-обработчик для элементов списка
 * метод ничего не возвращает
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
 * Метод getItemPtr
 * index - индекс элемента, ссылку на который нужно получить
 * метод возвращает ссылку на нужный элемент или nullptr, если такого индекса нет
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

/*
 * Метод isEmpty
 * index - индекс элемента, который нужно проверить
 * метод возвращает isEmpty элемента
 */
template<typename T>
bool LinkedList<T>::isEmpty(int index) {
    //если некорректный индекс
    if (index < 0)
        throw std::string("incorrect index");
    //переходим к нужному элементу
    item<T> *cur = first;
    for (int i = 0; i < index; ++i) {
        //если список закончился
        if (cur == nullptr)
            throw std::string("incorrect index");
        cur = cur->next;
    }
    return cur->isEmpty;
}

/*
 * Метод getSize
 * index - индекс элемента, ссылку на который нужно получить
 * метод возвращает ссылку на нужный элемент или nullptr, если такого индекса нет
 */
template<typename T>
int LinkedList<T>::getSize() {
    return size;
}