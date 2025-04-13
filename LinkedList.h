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
 * size - размер списка
 * pushBack - метод для вставки элемента в конец списка
 * pushBack - метод для получения ссылки на элемент по индексу
 * clear - очистка списка
 * print - метод для вывода элементов списка в консоль
 * sort - метод для сортировки списка
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

    void pushBack(T data);

    item<T> *getItemPtr(int index);

    void remove(int index);

    void print(void (*printer)(T item));

    void sort(int (*sorter)(T o1, T o2));

    int getSize();

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
 * метод ничего не возвращает
 */
template<typename T>
void LinkedList<T>::pushBack(T data) {
    //если список пустой, записываем первый элемент
    if (first == nullptr) {
        first = new item<T>(data, nullptr);
        size++;
        return;
    }
    //если список не пустой, доходим до последнего элемента и добавляем новый
    item<T> *cur = first;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = new item<T>(data, nullptr);
    size++;
}

/*
 * Метод clear
 * метод ничего не принимает
 * метод ничего не возвращает
 */
template<typename T>
void LinkedList<T>::remove(int index) {
    //если некорректный индекс
    if (index < 0)
        return;
    //переходим к нужному элементу
    item<T> *cur = first;
    item<T> *prev = nullptr;
    for (int i = 0; i < index; ++i) {
        //если список закончился
        if (cur == nullptr)
            return;
        if (i > 0)
            prev = cur;
        cur = cur->next;
    }
    if(prev != nullptr) {
        prev->next = cur->next;
    } else{
        first = cur->next;
    }
    size--;
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
void LinkedList<T>::sort(int (*sorter)(T o1, T o2)) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            item<T> *it1 = getItemPtr(j);
            item<T> *it2 = getItemPtr(j + 1);
            if (sorter(it1->data, it2->data) > 0) {
                T tempData = it1->data;
                it1->data = it2->data;
                it2->data = tempData;
            }
        }
    }
}

/*
 * Метод getItemPtr
 * index - индекс элемента, ссылку на который нужно получить
 * метод возвращает ссылку на нужный элемент или nullptr, если такого индекса нет
 */
template<typename T>
item<T> *LinkedList<T>::getItemPtr(int index) {
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
    return cur;
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