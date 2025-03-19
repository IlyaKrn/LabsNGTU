#include <iostream>
#include <fstream>

#include "BinaryTree.h"


using namespace std;

void getTreeFromFile(BinaryTree<int> *tree) {
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

            //проверка файла
            if(file.eof()) {
                repeat = true;
                cout << "can not parse file" << endl;
            }
            try{
                //получение глубины и корня дерева
                getline(file, input);
                deep = stoi(input);
                getline(file, input);
                int rootVal = stoi(input);
                *(tree) = BinaryTree<int>(rootVal);

                //очередь для текущего слоя, в который записывать дочерние элементы (добавляем корень)
                LinkedList<BinaryTree<int>*> queue = LinkedList<BinaryTree<int>*>();
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
//                    cout << endl;

                    //добавление в дерево
                    for (int j = 0; j < row.getSize(); j += 2) {
                        //текущее значение
                        int curLeft = *(row.getItemPtr(j));
                        int curRight = *(row.getItemPtr(j + 1));
                        bool isLeft = !row.isEmpty(j);
                        bool isRight = !row.isEmpty(j + 1);

                        //текущий узел
                        BinaryTree<int> *curRoot = *(queue.getItemPtr(queueIndex));
                        queueIndex++;

                        //добавляем дочерние узлы в дерево и очередь, если пустые,
                        //то в очереди помечием пустыми
                        if(isLeft){
                            curRoot->setLeftValue(curLeft);
                            queue.pushBack(curRoot->getLeftPtr(), false);
                        }
                        else{
                            queue.pushBack(nullptr, true);
                        }
                        if(isRight){
                            curRoot->setRightValue(curRight);
                            queue.pushBack(curRoot->getRightPtr(), false);
                        }
                        else{
                            queue.pushBack(nullptr, true);
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
    BinaryTree<int> root = BinaryTree<int>(0);
    getTreeFromFile(&root);


    //вывод результата в консоль
    cout << "=================================" << endl;
    root.print(printer);
    cout << "=================================" << endl;
    root.printBranchesWithMaxChildren(printer);
    cout << "=================================" << endl;


    return 0;
}