#include <iostream>
#include <fstream>
#include <algorithm>
#include "../include/SLAU.h"

using namespace std;

void printSLAU(SLAU slau){
    for (int i = 0; i < slau.n; ++i) {
        for (int j = 0; j < slau.n; ++j) {
            cout << slau.matrix[i][j] << "\t";
        }
        cout << "=  " << slau.matrix[i][slau.n] << "\n";
    }
}

vector<SLAU> getSLAUs(string filename){
    ifstream file(filename);
    vector<SLAU> slaus;

    while (true) {
        if (file.eof())
            break;

        SLAU slau;
        file >> slau.n;

        for (int i = 0; i < slau.n; ++i) {
            slau.matrix.push_back(vector<long double>());
            for (int j = 0; j < slau.n + 1; ++j) {
                long double a;
                file >> a;
                slau.matrix[i].push_back(a);
            }
        }

        slaus.push_back(slau);
    }

    return slaus;
}

SLAU solveSLAU(SLAU slau){
    for (int row = 1; row < slau.n; ++row) {
        int maxRowIndex = 0;
        long double maxEl = 0;
        for (int i = row - 1; i < slau.n; ++i) {
            if (abs(slau.matrix[i][row-1]) > abs(maxEl)){
                maxEl = slau.matrix[i][row-1];
                maxRowIndex = i;
            }
        }
        if(row-1 != maxRowIndex){
            vector<long double> temp = slau.matrix[row-1];
            slau.matrix[row-1] = slau.matrix[maxRowIndex];
            slau.matrix[maxRowIndex] = temp;
        }
        for (int i = row; i < slau.n; ++i) {
            long double mnozh = slau.matrix[i][row-1] / slau.matrix[row-1][row-1];
            for (int j = row-1; j < slau.n+1; ++j) {
                slau.matrix[i][j] -= mnozh * slau.matrix[row-1][j];
            }
            slau.matrix[i][row-1] = 0;
        }
    }
    return slau;
}


vector<long double> answerSLAU(SLAU slau){
    vector<long double> answer;
    for (int i = 0; i < slau.n; ++i) {
        answer.push_back(0);
    }

    for (int i = slau.n - 1; i >= 0; --i) {
        long double sum = 0;
        for (int j = 0; j < slau.n; ++j) {
            sum += answer[j] * slau.matrix[i][j];
        }
        answer[i] = (slau.matrix[i][slau.n] - sum) / slau.matrix[i][i];
    }

    return answer;
}