//Пусть слово - это последовательность от 1 до 8 символов, не включающая пробелов.
//Вводится n слов A1,...,An. Можно ли их переупорядочить так, чтобы получилась "цепочка",
//т.е. для каждого слова Aj его первая буква должна совпадать с последней буквой
//предыдущего слова, а последняя буква в Aj - с первой буквой последующего слова;
//соответственно последняя буква последнего слова должна совпадать с первой буквой
//первого слова. В цепочку входят все n слов без повторений.
//Дать ответ в виде "Можно"\"Нельзя".
//Если такое упорядочение возможно, то вывести какую-нибудь цепочку слов. Слова при выводе разделяются пробелами.



#include "LinkedList.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

//проверяем, можно ли составить цепочку
bool formChain(LinkedList<string> *list) {
    if (list->getSize() == 0) return false;

    //пытаемся составить цепочку
    list->sort([](string s1, string s2) {
        if (s1[s1.size() - 1] == s2[0])
            return -1;
        return 1;
    });

    //проверяем цепочку на правильность
    string prev = list->getItemPtr(list->getSize() - 1)->data;
    for (int i = 0; i < list->getSize(); i++) {
        if (list->getItemPtr(i)->data[0] != prev[prev.size() - 1])
            return false;
        prev = list->getItemPtr(i)->data;
    }
    return true;
}

int main() {
    LinkedList<string> list;
    ifstream file("../input.txt");

    // читаем файл и записываем слова
    if (!file.is_open()) {
        cout << "can not open file ../input.txt" << endl;
        return 1;
    }
    string line;
    while (getline(file, line)) {
        //проверяем слово на соответствие критериям задачи
        if (line.length() < 1 || line.length() > 8){
            cout << "word length must be in 1-8 chars" << endl;
            return 1;
        }
        list.pushBack(line);
    }
    file.close();
    // проверяем на цепочку и выводим результат
    if (!formChain(&list)) {
        cout << "Нельзя" << endl;
    } else{
        cout << "Можно" << endl;
        cout << "Цепочка: ";
        list.print([](string s){
            cout << s << " ";
        });
        cout << endl;
    }
    return 0;
}