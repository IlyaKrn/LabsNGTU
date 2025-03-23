#include <iostream>
#include <fstream>

#include "NTree.h"


using namespace std;

void getTreeFromFile(NTree<int> *tree) {
    bool repeat = false;
    do{
        // открытие файла
        string filepath;
        cout << "Enter path to file:" << endl;
        cin >> filepath;
//        filepath = "../input.txt";
        ifstream file(filepath);

        //если файл открыт
        if (file.is_open()){
            string input;
            int deep;
            int n;

            //проверка файла
            if(file.eof()) {
                repeat = true;
                cout << "can not parse file" << endl;
            }
            try{
                //получение глубины, n и корня дерева
                getline(file, input);
                deep = stoi(input);
                getline(file, input);
                n = stoi(input);
                getline(file, input);
                int rootVal = stoi(input);
                *(tree) = NTree<int>(rootVal, n);

                //очередь для текущего слоя, в который записывать дочерние элементы (добавляем корень)
                LinkedList<NTree<int>*> queue = LinkedList<NTree<int>*>();
                int queueIndex = 0;
                queue.pushBack(tree, false);

                //читаем строку из файла и записываем ее элементы в дерево
                for (int i = 1; i < deep; ++i) {
                    //проверка файла
                    if(file.eof()) {
                        repeat = true;
                        cout << "can not parse file" << endl;
                    }
                    //чтение строки
                    getline(file, input);
                    LinkedList<int> row;
                    string item;
                    for (int j = 0; j < input.size(); ++j) {
                        if(input.at(j) != ' '){
                            item += input.at(j);
                        }
                        else{
                            //записываем элемент и при необходимости помечаем его пустым
                            if(item == "-") {
                                row.pushBack(-1, true);
                            }
                            else{
                                row.pushBack(stoi(item), false);
                            }
                            item.clear();
                        }
                    }
                    //вывод прочитанных списков
//                    row.print([](int d, bool b){
//                        if(b){
//                            cout << "-";
//                        }
//                        else{
//                            cout << d;
//                        }
//                    });

                    //добавление в дерево
                    for (int j = 0; j < row.getSize(); j += n) {
                        //текущий узел
                        NTree<int> *curRoot = *(queue.getItemPtr(queueIndex));
                        queueIndex++;


                        //текущее значение
                        for (int k = 0; k < n; ++k) {
                            int curChild = *(row.getItemPtr(j + k));
                            bool isNotEmpty = !row.isEmpty(j + k);

                            if(isNotEmpty){
                                curRoot->addChild(curChild, false);
                                queue.pushBack(*(curRoot->getChildren().getItemPtr(k)), false);
                            }
                            else{
                                if(curRoot->getChildren().getSize() < n)
                                    curRoot->addChild(-1, true);
                                queue.pushBack(curRoot, true);
                            }
                        }
                    }
                }
            } catch (...){
                //ошибка чтения данных
                repeat = true;
                cout << "can not parse file" << endl;
                continue;
            }
            //закрываем файл и возвращаем матрицу CCS
            file.close();
            repeat = false;
        }
        else{
            //ошибка чтения файла
            repeat = true;
            cout << "can not read file" << endl;
        }
    } while (repeat);

}

int main() {
    //функция вывода элемента в консоль
    auto printer = [](int item, bool isEmpty) {
        cout << (isEmpty ? "-" : to_string(item));
    };

    //получение дерева
    NTree<int> root = NTree<int>();
    getTreeFromFile(&root);


    //вывод результата в консоль
    cout << "=================================" << endl;
    root.print(printer);
    cout << "=================================" << endl;
//    root.printSubTreesInRange(printer, 0, 1);
    cout << "=================================" << endl;


    return 0;
}