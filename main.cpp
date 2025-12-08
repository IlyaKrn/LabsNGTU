#include <iostream>
#include "./include/SLAU.h"

using namespace std;

int main(int argc, char** argv) {

    //получаем список слау
    vector<SLAU> slaus = getSLAUs("/home/ilyakrn/CLionProjects/LabsNGTU/nodes.txt");

    //решаем каждое последовательно
    for (int i = 0; i < slaus.size(); ++i) {
        SLAU rawSlau = slaus[i];
        SLAU solvedSlau = solveSLAU(rawSlau);
        vector<long double> answer = answerSLAU(solvedSlau);
        vector<long double> error = slauError(solvedSlau, answer);

        //выводим сырую слау
        cout << "\n\n============================\n";
        cout << "Исходная СЛАУ" << endl;
        printSLAU(rawSlau);
        cout << "Верхнетреугольная СЛАУ" << endl;
        printSLAU(solvedSlau);
        cout << "Вектор ответа" << endl;
        for (int j = 0; j < answer.size(); ++j) {
            cout << answer[j] << " ";
        }
        cout << "\nВектор невязки" << endl;
        for (int j = 0; j < error.size(); ++j) {
            cout << error[j] << " ";
        }
        cout << "\n\n============================\n";
    }





}