#include "include/SLAU.h"
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char** argv) {


    int n = 3;
    int m = -3;
    int maxIter = 7;
    long double eps = 1e-3;

    auto matrix = getInterpolationMatrix(n, 1, 0, 0, 0, [](long double x) -> long double {return 0;});

    cout << "Матрица задачи для n=" << n << endl;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.size(); ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Погрешность: " << eps << endl;
    cout << "Максимальное число итераций: " << maxIter << endl;
    cout << "Собственное значение при степенном методе:\n" << getLambdaStep(matrix, eps, maxIter) << endl;
    cout << "Собственное значение при методе обратных итераций и m = " << m << ":\n" << getLambdaBackIter(matrix, m, eps, maxIter) << endl;

}