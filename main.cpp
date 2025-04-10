#include <iostream>
#include <fstream>

#include "HashTable.h"

using namespace std;

int main() {
    HashTable<string> t = HashTable<string>();
    bool isInited = false;
    while (true){
        try{
            //вывод меню
            cout << "Действия:" << endl;
            cout << "1. записать информацию в пустую хеш таблицу" << endl;
            cout << "2. показ на экран хэш таблицы" << endl;
            cout << "3. добавление в хеш таблицу" << endl;
            cout << "4. функция удаления элементов" << endl;
            cout << "5. функция поиска по заданному ключу" << endl;
            //получение действия
            int action;
            string temp;
            cin >> temp;
            try {
                action = stoi(temp);
            }catch (...){
                cout << "неизвестное действие, попробуйте снова" << endl;
                continue;
            }

            auto printer = [](Key k, string i, bool b){
                if(!b) {
                    cout << k.lastName << "\t\t\t" << k.firstName << "\t\t\t" << k.middleName << "\t\t\t" << i << endl;
                }
            };
            //вызов соответствующей функциии
            switch (action) {
                case 1:
                    if(!isInited){
                        string firstName1;
                        string lastName1;
                        string middleName1;
                        string data;
                        cout << "Введите фамилию" << endl;
                        cin >> lastName1;
                        cout << "Введите имя" << endl;
                        cin >> firstName1;
                        cout << "Введите отчество" << endl;
                        cin >> middleName1;
                        cout << "Введите данные" << endl;
                        cin >> data;
                        t.init(Key(firstName1, lastName1, middleName1), data);
                        isInited = true;
                    } else{
                        cout << "таблица уже создана, попробуйте снова" << endl;
                    }
                    break;
                case 2:
                    if(isInited){
                        cout << "таблица:" << endl;
                        t.print(printer);
                    } else{
                        cout << "таблица ещё не создана, попробуйте снова" << endl;
                    }
                    break;
                case 3:
                    if(isInited){
                        string firstName2;
                        string lastName2;
                        string middleName2;
                        string data;
                        cout << "Введите фамилию" << endl;
                        cin >> lastName2;
                        cout << "Введите имя" << endl;
                        cin >> firstName2;
                        cout << "Введите отчество" << endl;
                        cin >> middleName2;
                        cout << "Введите данные" << endl;
                        cin >> data;
                        t.add(Key(firstName2, lastName2, middleName2), data);
                    } else{
                        cout << "таблица ещё не создана, инициализируйте и попробуйте снова" << endl;
                    }
                    break;
                case 4:
                    if(isInited){
                        string firstName3;
                        string lastName3;
                        string middleName3;
                        cout << "Введите фамилию" << endl;
                        cin >> lastName3;
                        cout << "Введите имя" << endl;
                        cin >> firstName3;
                        cout << "Введите отчество" << endl;
                        cin >> middleName3;
                        t.remove(Key(firstName3, lastName3, middleName3));
                    } else{
                        cout << "таблица ещё не создана, инициализируйте и попробуйте снова" << endl;
                    }
                    break;
                case 5:
                    if(isInited){
                        string firstName4;
                        string lastName4;
                        string middleName4;
                        cout << "Введите фамилию" << endl;
                        cin >> lastName4;
                        cout << "Введите имя" << endl;
                        cin >> firstName4;
                        cout << "Введите отчество" << endl;
                        cin >> middleName4;
                        cout << "результат поиска:" << endl;
                        cout << t.find(Key(firstName4, lastName4, middleName4)) << endl;
                    } else{
                        cout << "таблица ещё не создана, инициализируйте и попробуйте снова" << endl;
                    }
                    break;
                default:
                    cout << "неизвестное действие, попробуйте снова" << endl;
            }

        } catch (...){
            cout << "неизвестное ошибка, попробуйте снова" << endl;
        }
    }

    return 0;
}