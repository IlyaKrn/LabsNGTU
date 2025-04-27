#include <iostream>
#include <fstream>

#include "CCSMatrix.h"


using namespace std;

//Функция чтения матрицы из файла
CCSMatrix<int> getMatrixFromFile() {
    bool repeat = false;
    do{
        // открытие файла
        string filepath;
        cout << "Enter path to file:" << endl;
        cin >> filepath;
        ifstream file(filepath);

        //если файл открыт
        if (file.is_open()){
            string input;
            //читаем ширину и высоту
            LinkedList<LinkedList<int>> matrix;
            int height;
            int width;

            //проверка файла
            if(file.eof()) {
                repeat = true;
                cout << "can not parse file" << endl;
            }
            try{
                getline(file, input);
                height = stoi(input.substr(0, input.find(" ")));
                width = stoi(input.substr(input.find(" ")));
            } catch (...){
                //ошибка чтения данных
                repeat = true;
                cout << "can not parse file" << endl;
            }
            try{
                //читаем строку из файла и записываем ее элементы в массив
                for (int i = 0; i < height; ++i) {
                    //проверка файла
                    if(file.eof()) {
                        repeat = true;
                        cout << "can not parse file" << endl;
                    }
                    getline(file, input);
                    LinkedList<int> row;
                    string item;
                    for (int j = 0; j < input.size(); ++j) {
                        if(input.at(j) != ' '){
                            item += input.at(j);
                        }
                        else{
                            row.pushBack(stoi(item));
                            item.clear();
                        }
                    }
                    matrix.pushBack(row);
                }
            } catch (...){
                repeat = true;
                cout << "can not parse file" << endl;
            }
            //закрываем файл и возвращаем матрицу CCS
            file.close();
            repeat = false;
            return CCSMatrix<int>(matrix, height, width, 0);
        }
        else{
            //ошибка чтения файла
            repeat = true;
            cout << "can not read file" << endl;
        }
    } while (repeat);

}

int mainy() {
    try{
        CCSMatrix<int> matrix = getMatrixFromFile();
        auto printer = [](int item){
            cout << item << " ";
        };
        matrix.printAsCCS(printer);
        matrix.printAsMatrix(printer, 0);
        matrix.getEvenIndexElements(printer);
    } catch (string e){
        cout << e << endl;
        return 1;
    }
    return 0;
}