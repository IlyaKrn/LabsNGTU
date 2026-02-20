#include <iostream>
#include <algorithm>
#include <cmath>
#include "../include/SLAU.h"

using namespace std;

vector<long double> solveSLAU(vector<vector<long double>> matrix){
    for (int row = 1; row < matrix.size(); ++row) {
        int maxRowIndex = 0;
        long double maxEl = 0;
        for (int i = row - 1; i < matrix.size(); ++i) {
            if (abs(matrix[i][row-1]) > abs(maxEl)){
                maxEl = matrix[i][row-1];
                maxRowIndex = i;
            }
        }
        if(row-1 != maxRowIndex){
            vector<long double> temp = matrix[row-1];
            matrix[row-1] = matrix[maxRowIndex];
            matrix[maxRowIndex] = temp;
        }
        for (int i = row; i < matrix.size(); ++i) {
            long double mnozh = matrix[i][row-1] / matrix[row-1][row-1];
            for (int j = row-1; j < matrix.size()+1; ++j) {
                matrix[i][j] -= mnozh * matrix[row-1][j];
            }
            matrix[i][row-1] = 0;
        }
    }

    vector<long double> answer;
    for (int i = 0; i < matrix.size(); ++i) {
        answer.push_back(0);
    }

    for (int i = matrix.size() - 1; i >= 0; --i) {
        long double sum = 0;
        for (int j = 0; j < matrix.size(); ++j) {
            sum += answer[j] * matrix[i][j];
        }
        answer[i] = (matrix[i][matrix.size()] - sum) / matrix[i][i];
    }

    return answer;
}

vector<vector<long double>> getJacobean(vector<long double> X){
    vector<vector<long double>> result = {
            {-sin(0.4 * X[1] + X[0] * X[0]) * 2 * X[0] + 2 * X[0], -sin(0.4 * X[1] + X[0] * X[0]) * 0.4 + 2 * X[1]},
            {3 * X[0], -X[1] / 0.18}
    };
    return result;
}

vector<long double> getFuncErr(vector<long double> X){
    vector<long double> result = {
        cos(0.4 * X[1] + X[0] * X[0]) + X[1] * X[1] + X[0] * X[0] - 1.6,
        1.5 * X[0] * X[0] - ((X[1] * X[1]) / 0.36) - 1
    };
    return result;
}

vector<long double> solveSNAU(vector<long double> start){

    //начальные данные
    int k = 0;
    long double e1 = 1e-9;
    long double e2 = 1e-9;
    int maxIter = 1000;

    //приближение предыдущей итерации
    vector<long double> Xk = {start[0], start[1]};

    //нормы ошибок предыдущей итерации
    long double d2 = e2*2;
    long double d1 = e1*2;

    //выводим начальные данные
    cout << "Начальное приближение: (" << Xk[0] << " " << Xk[1] << ")" << endl;
    cout << "Заданная погрешность: е1 = " << e1 << "; e2 = " << e2 << endl;
    cout << "Предельное число итераций: " << maxIter << endl;

    //начинаем итерации
    while (d1 > e1 || d2 > e2){
        k++;

        //если итераций слишком много, выходим с ошибкой
        if (k > maxIter){
            cout << "iteration limit error" << endl;
            break;
        }

        //получаем матрицу Якоби и вектор невязки
        vector<vector<long double>> Jk = getJacobean(Xk);
        vector<long double> Fk = getFuncErr(Xk);

        //решаем СЛАУ для нахождения дельты
        vector<long double> Dxk = solveSLAU({
                                                    {Jk[0][0], Jk[0][1], -Fk[0]},
                                                    {Jk[1][0], Jk[1][1], -Fk[1]},
                                            });


        //получаем следующее приближение
        vector<long double> Xk1 = {
                Xk[0] + Dxk[0],
                Xk[1] + Dxk[1],
        };

        //пересчитываем нормы
        d1 = 0;
        d2 = 0;
        for (int i = 0; i < Fk.size(); ++i) {
            if (d1 < abs(Fk[i]))
                d1 = abs(Fk[i]);
        }
        if(sqrt(Xk1[0]*Xk1[0] + Xk1[1]*Xk1[1]) < 1){
            for (int i = 0; i < Fk.size(); ++i) {
                long double tmp = Xk1[i] - Xk[i];
                if (d2 < abs(tmp)) {
                    d2 = abs(tmp);
                }
            }
        }
        else {
            for (int i = 0; i < Fk.size(); ++i) {
                long double tmp = (Xk1[i] - Xk[i]) / Xk1[i];
                if (d2 < abs(tmp)) {
                    d2 = abs(tmp);
                }
            }
        }

        //переходим в новому приближению
        Xk = Xk1;

        cout << "Итерация " << k << ": d1 = " << d1 << "; d2 = " << d2 << endl;
        cout << "k-тое приближение: (" << Xk[0] << " " << Xk[1] << ")" << endl;

    }
    cout << "Приближенное решение:\n" << Xk[0] << "\t\t" << Xk[1] << endl;
    return Xk;

}