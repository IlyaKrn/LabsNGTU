#pragma once
#include <string>
#include <math.h>
#include <bitset>
#include <set>


/*
 * Структура Key - ключ в таблице
 * firstName - имя
 * lastName - фамилия
 * middleName - отчество
 * Key - конструктор (пустой и со всеми полями)
 */
struct Key {
    std::string firstName;
    std::string lastName;
    std::string middleName;

    Key() {}

    Key(std::string firstName, std::string lastName, std::string middleName) :
    firstName(firstName), lastName(lastName), middleName(middleName) {}
};

/*
 * Структура Item - элемент таблицы
 * key - ключ
 * value - значение
 * isEmpty - удален элемент или нет
 * Item - конструктор
 */
template<typename T>
struct Item {
    Key key;
    T value;
    bool isEmpty;

    Item() {}
};

/*
 * Класс HashTable - хэш таблица
 * currentSize - текущий размер
 * currentFilling - текущая заполненность
 * array - список с элементами
 * getNewHash - метод получения нового хэша
 * getExistingHash - метод получения хэша существующего элемента
 * rehashTable - метод рехэширования
 * init - метод для записи первого значения
 * add - метод для записи следующих значений
 * find - метод для поиска
 * remove - метод для удаления
 * print - метод вывода таблицы в консоль
 */
template<typename T>
class HashTable {
private:
    int currentSize;
    int currentFilling;
    Item<T>* array;


    int getNewHash(Key fio);
    int getExistingHash(Key fio);
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
    delete[] array;
}

/*
 * метод init
 * key - ключ для добавления
 * value - значение для добавления
 * метод ничего не возвращает
 */
template<typename T>
void HashTable<T>::init(Key key, T value) {
    // проверяем инициализированность
    if(currentSize == -1){
        // инициализируем
        currentSize = 4;
        currentFilling = 0;
        array = new Item<T>[currentSize];
        for (int i = 0; i < currentSize; ++i) {
            array[i].isEmpty = true;
        }
    }
    add(key, value);
}

/*
 * метод add
 * key - ключ для добавления
 * value - значение для добавления
 * метод ничего не возвращает
 */
template<typename T>
void HashTable<T>::add(Key key, T value) {
    //проверяем нужно ли рехэшировать
    if (currentFilling > (currentSize * 0.7)){
        rehashTable(currentSize * 2);
    }
    //добавляем по новому хэшу
    int itemHash = getNewHash(key);
    array[itemHash].key = key;
    array[itemHash].value = value;
    array[itemHash].isEmpty = false;
    currentFilling++;
}

/*
 * метод remove
 * key - ключ для удаления
 * метод ничего не возвращает
 */
template<typename T>
void HashTable<T>::remove(Key key) {
    //удаляем по хэшу
    int itemHash = getExistingHash(key);
    array[itemHash].isEmpty = true;
    currentFilling--;
}

/*
 * метод find
 * key - ключ для поиска
 * метод возвращает значение для ключа или пустую структуру
 */
template<typename T>
T HashTable<T>::find(Key key) {
    //находим по хэшу
    int itemHash = getExistingHash(key);
    return array[itemHash].value;
}

/*
 * метод print
 * printer - функция вывода элемента в консоль
 * метод ничего не возвращает
 */
template<typename T>
void HashTable<T>::print(void (*printer)(Key, T, bool)) {
    //выводим все элементы
    for (int i = 0; i < currentSize; ++i) {
        printer(array[i].key, array[i].value, array[i].isEmpty);
    }
}

template<typename T>
int HashTable<T>::getNewHash(Key fio) {
    //преобразуем ключ в число
    std::string keyString = fio.lastName + "$" + fio.firstName + "$" + fio.middleName;
    int keyNum = 0;
    for (int i = 0; i < keyString.size(); ++i) {
        keyNum += (keyString.at(i) * keyString.at(i));
    }
    keyNum = abs(keyNum);
    //получаем минимальное количество бит для хэша
    int bitsToSize = 0;
    int temp = 2;
    while (temp <= currentSize){
        bitsToSize++;
        temp *= 2;
    }
    //генерируем хэш
    int offset = (32 - bitsToSize) / 2;
    int tempHash = keyNum * keyNum;

    std::string hashString = std::bitset<32>(tempHash).to_string();
    hashString = hashString.substr(offset);
    hashString = hashString.substr(0, bitsToSize);
    tempHash = std::stoi(hashString, nullptr, 2);
    tempHash %= currentSize;

    //решаем коллизию
    int attempt = 1;
    int hash = tempHash;
    while (!array[hash].isEmpty){
        hash = (tempHash + 3 * attempt + 2 * attempt * attempt) % currentSize;
        attempt++;
    }

    return hash;
}

/*
 * метод rehashTable
 * newSize - новый размер таблицы
 */
template<typename T>
void HashTable<T>::rehashTable(int newSize) {
    //создаем новый массив и заполняем его пустыми элементами
    Item<T>* oldArray = array;
    array = new Item<T>[newSize];
    for (int i = 0; i < newSize; ++i) {
        array[i].isEmpty = true;
    }
    //копируем элементы из старого массива в новый с новыми хэшами
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
    //удаляем старый массив
    delete[] oldArray;

}

/*
 * метод getExistingHash
 * fio - ключ для поиска
 * метод ничего не возвращает
 */
template<typename T>
int HashTable<T>::getExistingHash(Key fio) {
    //преобразуем ключ в число
    std::string keyString = fio.lastName + "$" + fio.firstName + "$" + fio.middleName;
    int keyNum = 0;
    for (int i = 0; i < keyString.size(); ++i) {
        keyNum += (keyString.at(i) * keyString.at(i));
    }
    keyNum = abs(keyNum);
    //получаем минимальное количество бит для хэша
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

    //при коллизии решаем ее до тех пор, пока не найдем элемент или не переберем весь массив
    int attempt = 1;
    int hash = tempHash;
    while (array[hash].isEmpty ||
           array[hash].key.firstName != fio.firstName ||
           array[hash].key.lastName != fio.lastName ||
           array[hash].key.middleName != fio.middleName
    ){
        hash = (tempHash + 3 * attempt + 2 * attempt * attempt) % currentSize;
        attempt++;
        if(attempt == currentSize){
            hash = -1;
            break;
        }
    }
    // возвращаем найденный хэш или -1

    return hash;
}



