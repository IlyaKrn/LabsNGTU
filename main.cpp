#include <iostream>
#include <fstream>

#include "LinkedList.h"


using namespace std;

/* Функция чтения списка из консоли
 * listPtr - указатель на список, в который нужно произвести запись
 * shiftPtr - указатель на сдвиг, который нужно записать
 * функция ничего не возвращает
*/
void getListFromConsole(LinkedList<int>* listPtr, int* shiftPtr){
    //заполнение списка из консоли
    cout << "enter integer elements (to separate press ENTER, to stop enter STOP):" << endl;
    string input;
    while (true){
        int newElement;
        cin >> input;
        //проверка завершения чтения
        if(input == "STOP")
            break;
        // проверка корректности
        try{
            newElement = stoi(input);
        } catch (...){
            cout << "wrong input, try again" << endl;
            continue;
        }
        listPtr->pushBack(newElement);
    }
    //чтение сдвига
    cout << "enter shift (positive integer):" << endl;
    while (true){
        int shift;
        cin >> input;
        // проверка корректности
        try{
            shift = stoi(input);
        } catch (...){
            cout << "wrong input, try again" << endl;
            continue;
        }
        if(shift < 0){
            cout << "wrong input, try again" << endl;
            continue;
        }
        *shiftPtr = shift;
        break;
    }
}

/* Функция чтения списка из файла
 * listPtr - указатель на список, в который нужно произвести запись
 * shiftPtr - указатель на сдвиг, который нужно записать
 * filePath - путь до файла
 * функция возвращает 0 в случае успешного выполнения, 1 в случае ошибки чтения данных
*/
int getListFromFile(LinkedList<int>* listPtr, int* shiftPtr, const string& filePath){
    ifstream file(filePath);
    if (file.is_open()){
        //заполнение списка из файла
        string input;
        while (getline(file, input) || !file.eof()) {
            int newElement;
            //проверка завершения чтения
            if(input == "STOP")
                break;
            //проверка корректности
            try{
                newElement = stoi(input);
            } catch (...){
                return 1;
            }
            listPtr->pushBack(newElement);
        }
        if(file.eof())
            return 1;
        //чтение сдвига
        while (getline(file, input) || !file.eof()){
            int shift;
            // проверка корректности
            try{
                shift = stoi(input);
            } catch (...){
                return 1;
            }
            if(shift < 0){
                return 1;
            }
            *shiftPtr = shift;
            break;
        }
        file.close();
    }
    else{
        return 1;
    }
    return 0;
}

int main() {

    //чтение списка и сдвига
    LinkedList<int> linkedList = LinkedList<int>();
    int shift;
    while (true){
        //выбор метода ввода
        cout << "Read from file or console [f/c]?";
        string readType;
        cin >> readType;
        if(readType == "f") {
            cout << "enter path to file" << endl;
            string path;
            cin >> path;
            int code = getListFromFile(&linkedList, &shift, path);
            //если произошла ошибка, стираем записанные данные и повторяем
            if(code != 0) {
                cout << "wrong read file" << endl;
                linkedList.clear();
                continue;
            }
            break;
        }
        else if(readType == "c") {
            getListFromConsole(&linkedList, &shift);
            break;
        }
        else {
            cout << "wrong input, try again" << endl;
            continue;
        }
    }

    // функция вывода элемента списка в консоль
    auto printer = [](int item){
        cout << item;
    };

    // циклический сдвиг на заданную величину с выводом списка в консоль
    cout << "pre:" << endl;
    linkedList.print(printer);

    linkedList.cyclicShiftLeft(shift);

    cout << "post:" << endl;
    linkedList.print(printer);

    return 0;
}