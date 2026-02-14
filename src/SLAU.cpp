#include <iostream>
#include <algorithm>
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
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout<< endl;
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