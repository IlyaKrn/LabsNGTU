#pragma once
#include <string>

// Реализовать алгоритмы поиска, вставки, удаления элементов таблицы и распечатки таблицы
// и метод ре-хэширования таблицы при увеличении размера данных.

//Фамилия Имя Отчество - Ключ
//функция «середины квадрата» - Хэш-функция
//Квадратичное опробование - Метод разрешения коллизий

//В 5 лабе обязательно меню, в котором прописаны все действия
//1. записать информацию в пустую хеш таблицу (вызывается один раз)
//2. показ на экран хэш таблицы
//3. добавление в хеш таблицу
//4. функция удаления элементов
//5. функция поиска по заданному ключу

//////////////////////////////////////////////////////////////////

//адрес=h(x)+ci+di2 - квадр опроб

struct Key {
    std::string firstName;
    std::string lastName;
    std::string middleName;
};

template<typename T>
struct Item {
    Key key;
    T value;
    bool isEmpty;
};

template<typename T>
class HashTable {
private:
    int currentSize;
    int currentFilling;
    Item<T>* array;


    int getNewHash(Key fio); // возвращает новый хэш без коллизий
    int getExistingHash(Key fio); // Возвращает хэш элемента по ключу (для получений элемента. Фикс ошибок коллизий)
    void rehashTable(int newSize);


public:
    HashTable();
    ~HashTable();
    void init(Key key, T value);
    void add(Key key, T value);
    T* find(Key key);
    void remove(Key key);
    void print(void (*printer)(Key, T, bool));

};

template<typename T>
HashTable<T>::HashTable() {
    currentSize = -1;
    currentFilling = -1;
}

template<typename T>
HashTable<T>::~HashTable() {
    delete array;
}

template<typename T>
void HashTable<T>::init(Key key, T value) {
    if(currentSize == -1){
        currentSize = 64;
        currentFilling = 0;
        array = new Item<T>[currentSize];
        for (int i = 0; i < currentSize; ++i) {
            array[i].isEmpty = true;
        }
    }
    add(key, value);
}

template<typename T>
void HashTable<T>::add(Key key, T value) {
    if (currentFilling > (currentSize * 0.7)){
        rehashTable(currentSize * 2);
    }
    int itemHash = getNewHash(key);
    array[itemHash].key = key;
    array[itemHash].value = value;
    array[itemHash].isEmpty = false;
    currentSize++;
}

template<typename T>
void HashTable<T>::remove(Key key) {
    int itemHash = getExistingHash(key);
    array[itemHash].isEmpty = true;
    currentSize--;
}

template<typename T>
T *HashTable<T>::find(Key key) {
    int itemHash = getExistingHash(key);
    return array[itemHash];
}

template<typename T>
void HashTable<T>::print(void (*printer)(Key, T, bool)) {
    for (int i = 0; i < currentSize; ++i) {
        printer(array[i].key, array[i].value, array[i].isEmpty);
    }
}



