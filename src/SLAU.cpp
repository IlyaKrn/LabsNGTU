#include "../include/SLAU.h"
#include <iostream>
#include <cmath>

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

vector<vector<long double>> getInterpolationMatrix(int n, long double h, long double x0, long double U0, long double Un, function<long double(long double)> f){
    vector<vector<long double>> matrix;
    for (int i = 0; i < n; ++i) {
        matrix.push_back(vector<long double>());
        for (int j = 0; j < n; ++j) {
            if(i == j) matrix[i].push_back(-2);
            else if(i == j + 1 || i == j - 1) matrix[i].push_back(1);
            else matrix[i].push_back(0);
        }
    }
    for (int i = 0; i < n; ++i) {
        matrix[i].push_back(f(x0 + h * i) * h * h);
    }
    matrix[0][n] -= U0;
    matrix[n-1][n] -= Un;
    return matrix;
}

long double scalar(vector<long double> v1, vector<long double> v2){
    long double s = 0;
    for (int i = 0; i < v1.size(); ++i) {
        s += v1[i]*v2[i];
    }
    return s;
}

long double norm(vector<long double> v){
    long double n = 0;
    for (int i = 0; i < v.size(); ++i) {
        n += v[i]*v[i];
    }
    return sqrt(n);
}

vector<long double> normed(vector<long double> v){
    long double n = norm(v);
    for (int i = 0; i < v.size(); ++i) {
        v[i] /= n;
    }
    return v;
}

long double getLForVector(vector<vector<long double>> matrix, vector<long double> v){
    vector<long double> v1 = v;
    for (int j = 0; j < matrix.size(); ++j) {
        v1[j] = 0;
        for (int k = 0; k < matrix.size(); ++k) {
            v1[j] += matrix[j][k] * v[k];
        }
    }
    return scalar(v1, v)/scalar(v, v);
}

long double getLambdaStep(vector<vector<long double>> matrix, long double eps, int maxIter){
    //начальный вектор
    vector<long double> Yk;
    for (int i = 0; i < matrix.size(); ++i) {
        Yk.push_back(1);
    }

    //новый вектор
    vector<long double> Yk1 = Yk;
    int iter = 0;
    while (true){
        iter++;
        //слишком много итераций
        if(iter >= maxIter){
            cerr << "iter limit error!" << endl;
            break;
        }
        //переходим к вектору из предыдущей итерации и вычисляем новый
        Yk = Yk1;
        for (int j = 0; j < matrix.size(); ++j) {
            Yk1[j] = 0;
            for (int k = 0; k < matrix.size(); ++k) {
                Yk1[j] += matrix[j][k] * Yk[k];
            }
        }
        Yk1 = normed(Yk1);

        //если собственное число изменилось достаточно мало с предыдущей итерации,
        //то считаем что вектор найден
        if(abs(getLForVector(matrix, Yk1) - getLForVector(matrix, Yk)) < eps)
            break;
    }

    return getLForVector(matrix, Yk1);
}

long double getLambdaBackIter(vector<vector<long double>> matrix, long double m, long double eps, int maxIter){
    //начальный вектор
    vector<long double> Yk;
    for (int i = 0; i < matrix.size(); ++i) {
        Yk.push_back(1);
    }

    //добавляем правую часть и вычитаем единичную матрицу * m
    vector<vector<long double>> matrixForSlau = matrix;
    for (int i = 0; i < matrixForSlau.size(); ++i) {
        matrixForSlau[i].push_back(0);
        matrixForSlau[i][i] -= m;
    }

    //новый вектор
    vector<long double> Yk1 = Yk;
    int iter = 0;
    while (true){
        iter++;
        //слишком много итераций
        if(iter >= maxIter){
            cerr << "iter limit error!" << endl;
            break;
        }
        //переходим к вектору из предыдущей итерации и вычисляем новый
        Yk = Yk1;
        for (int j = 0; j < matrixForSlau.size(); ++j) {
            matrixForSlau[j][matrixForSlau.size()] = Yk[j];
        }
        Yk1 = normed(solveSLAU(matrixForSlau));

        //если собственное число изменилось достаточно мало с предыдущей итерации,
        //то считаем что вектор найден
        if(abs(getLForVector(matrix, Yk1) - getLForVector(matrix, Yk)) < eps)
            break;
    }

    return getLForVector(matrix, Yk1);
}