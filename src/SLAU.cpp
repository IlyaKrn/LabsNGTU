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

vector<vect_t> explicitSchema(function<long double(long double)> fi, std::function<long double(long double, long double)> f, function<long double(long double)> g1, function<long double(long double)> g2, long double a, long double T1, long double T2, long double X1, long double X2, int Tn){
    vector<vect_t> result;

    //вычисляем количество точек сетки
    int Xn = (X2-X1)*sqrt(Tn/(2*a*(T2-T1))) - 1;

    //вычисляем начальные значения
    vect_t start = {{}, {}, T1};
    for (int i = 0; i <= Xn; ++i) {
        long double curX = X1 + i * (X2-X1) / Xn;
        start.X.push_back(curX);
        start.U.push_back(fi(curX));
    }
    result.push_back(start);

    //находим следующие слои явным методом
    for (int i = 1; i <= Tn; ++i) {
        vect_t ll = result[result.size()-1];
        long double curT = T1 + i * (T2-T1) / Tn;
        vect_t curLayer = {{}, {}, curT};
        curLayer.X = start.X;
        curLayer.U.push_back(-g1(curT)*(X2-X1)/Xn+ll.U[1]);
        for (int j = 1; j < curLayer.X.size() - 1; ++j) {
            curLayer.U.push_back(
                    ll.U[j] + (a*(T2-T1)*Xn*Xn) / (Tn*(X2-X1)*(X2-X1))
                    * (ll.U[j+1] - 2*ll.U[j] + ll.U[j-1]) + f(curLayer.X[j], curT)
            );
        }
        curLayer.U.push_back(g2(curT)*(X2-X1)/Xn+ll.U[ll.U.size()-2]);
        result.push_back(curLayer);
    }

    return result;
    
}

vector<vect_t> nonExplicitSchema(function<long double(long double)> fi, std::function<long double(long double, long double)> f, function<long double(long double)> g1, function<long double(long double)> g2, long double a, long double T1, long double T2, long double X1, long double X2, int Tn){
    vector<vect_t> result;

    //вычисляем количество точек сетки
    int Xn = (X2-X1)*sqrt(Tn/(2*a*(T2-T1))) - 1;

    //параметр схемы
    long double tau = (T2 - T1) / Tn;
    long double h = (X2 - X1) / Xn;
    long double r = a * tau / (h * h);

    //вычисляем начальные значения
    vect_t start = {{}, {}, T1};
    for (int i = 0; i <= Xn; ++i) {
        long double curX = X1 + i * h;
        start.X.push_back(curX);
        start.U.push_back(fi(curX));
    }
    result.push_back(start);

    int N = Xn + 1;
    //находим следующие слои неявным методом
    for (int i = 1; i <= Tn; ++i) {
        vect_t ll = result.back();
        long double curT = T1 + i * tau;
        vect_t curLayer = {{}, {}, curT};
        curLayer.X = start.X;

        vector<vector<long double>> slau(N, vector<long double>(N + 1, 0));

        slau[0][0] = 2 * (1 + r);
        slau[0][1] = -2 * r;

        slau[0][N] =
                2 * (1 - r) * ll.U[0]
                + 2 * r * ll.U[1]
                + 2 * r * h * g1(curT)
                + f(curLayer.X[0], curT);

        for (int j = 1; j < N - 1; ++j) {
            slau[j][j-1] = -r;
            slau[j][j]= 2 * (1 + r);
            slau[j][j+1] = -r;
            slau[j][N] =
                    r * ll.U[j - 1]
                    + 2 * (1 - r) * ll.U[j]
                    + r * ll.U[j + 1]
                    + f(curLayer.X[j], curT);
        }

        slau[N - 1][N - 2] = -2 * r;
        slau[N - 1][N - 1] = 2 * (1 + r);

        slau[N - 1][N] =
                2 * r * ll.U[N - 2]
                + 2 * (1 - r) * ll.U[N - 1]
                - 2 * r * h * g2(curT)
                + f(curLayer.X[N - 1], curT);

        vector<long double> solution = solveSLAU(slau);

        curLayer.U = solution;

        result.push_back(curLayer);
    }

    return result;
}