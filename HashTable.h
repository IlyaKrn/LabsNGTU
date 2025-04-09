#pragma once
#include <string>
#include <math.h>
#include <bitset>
#include <set>

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

    Key() {}

    Key(std::string firstName, std::string lastName, std::string middleName) :
    firstName(firstName), lastName(lastName), middleName(middleName) {}
};

template<typename T>
struct Item {
    Key key;
    T value;
    bool isEmpty;

    Item() {}
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
    T find(Key key);
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
//    delete array;
}

template<typename T>
void HashTable<T>::init(Key key, T value) {
    if(currentSize == -1){
        currentSize = 4;
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
    currentFilling++;
}

template<typename T>
void HashTable<T>::remove(Key key) {
    int itemHash = getExistingHash(key);
    array[itemHash].isEmpty = true;
    currentFilling--;
}

template<typename T>
T HashTable<T>::find(Key key) {
    int itemHash = getExistingHash(key);
    return array[itemHash].value;
}

template<typename T>
void HashTable<T>::print(void (*printer)(Key, T, bool)) {
    for (int i = 0; i < currentSize; ++i) {
        printer(array[i].key, array[i].value, array[i].isEmpty);
    }
}

template<typename T>
int HashTable<T>::getNewHash(Key fio) {
    std::string keyString = fio.lastName + "$" + fio.firstName + "$" + fio.middleName;
    int keyNum = 0;
    for (int i = 0; i < keyString.size(); ++i) {
        keyNum += (keyString.at(i) * keyString.at(i));
    }
    keyNum = abs(keyNum);
    int bitsToSize = 0;
    int temp = 2;
    while (temp <= currentSize){
        bitsToSize++;
        temp *= 2;
    }
    int offset = (32 - bitsToSize) / 2;
    int tempHash = keyNum * keyNum;

    std::string hashString = std::bitset<32>(tempHash).to_string();
    hashString = hashString.substr(offset);
    hashString = hashString.substr(0, bitsToSize);
    tempHash = std::stoi(hashString, nullptr, 2);
    tempHash %= currentSize;

    int attempt = 1;
    int hash = tempHash;
    while (!array[hash].isEmpty){
        hash = (tempHash + 3 * attempt + 2 * attempt * attempt) % currentSize;
        attempt++;
    }

    return hash;
}

template<typename T>
void HashTable<T>::rehashTable(int newSize) {
    Item<T>* oldArray = array;
    array = new Item<T>[newSize];
    for (int i = 0; i < newSize; ++i) {
        array[i].isEmpty = true;
    }
    for (int i = 0; i < currentSize; ++i) {
        Item<T> item = oldArray[i];
        if(!item.isEmpty) {
            int newHash = getNewHash(item.key);
            array[newHash].key = item.key;
            array[newHash].value = item.value;
            array[newHash].isEmpty = false;
        }
    }
    currentSize = newSize;
//    delete oldArray;

}

template<typename T>
int HashTable<T>::getExistingHash(Key fio) {
    std::string keyString = fio.lastName + "$" + fio.firstName + "$" + fio.middleName;
    int keyNum = 0;
    for (int i = 0; i < keyString.size(); ++i) {
        keyNum += (keyString.at(i) * keyString.at(i));
    }
    keyNum = abs(keyNum);
    int bitsToSize = 0;
    int temp = 2;
    while (temp <= currentSize){
        bitsToSize++;
        temp *= 2;
    }
    int offset = (32 - bitsToSize) / 2;
    int tempHash = keyNum * keyNum;

    std::string hashString = std::bitset<32>(tempHash).to_string();
    hashString = hashString.substr(offset);
    hashString = hashString.substr(0, bitsToSize);
    tempHash = std::stoi(hashString, nullptr, 2);
    tempHash %= currentSize;

    int attempt = 1;
    int hash = tempHash;
    while (array[hash].isEmpty ||
           array[hash].key.firstName != fio.firstName ||
           array[hash].key.lastName != fio.lastName ||
           array[hash].key.middleName != fio.middleName
    ){
        hash = (tempHash + 3 * attempt + 2 * attempt * attempt) % currentSize;
        attempt++;
    }

    return hash;
}



