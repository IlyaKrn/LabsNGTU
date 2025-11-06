#include "../include/ApproximatedFunctions.h"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

vector<node> getNodes(string filePath){
    vector<node> nodes;
    ifstream file(filePath);
    long double x, y;
    while (file >> x >> y){
        nodes.push_back({x / 10,100* (- y / 10) + 99});
    }
    return nodes;
}

vector<long double> minSquaresApproximation(long double x, vector<node> nodes){
    vector<long double> values;

    long double x0 = 0;
    long double x1 = 0;
    long double x2 = 0;
    long double x3 = 0;
    long double x4 = 0;
    long double x5 = 0;
    long double x6 = 0;

    long double y = 0;
    long double yx1 = 0;
    long double yx2 = 0;
    long double yx3 = 0;

    for (int i = 0; i < nodes.size(); ++i) {
        x0 += 1;
        x1 += nodes[i].x;
        x2 += nodes[i].x * nodes[i].x;
        x3 += nodes[i].x * nodes[i].x * nodes[i].x;
        x4 += nodes[i].x * nodes[i].x * nodes[i].x * nodes[i].x;
        x5 += nodes[i].x * nodes[i].x * nodes[i].x * nodes[i].x * nodes[i].x;
        x6 += nodes[i].x * nodes[i].x * nodes[i].x * nodes[i].x * nodes[i].x * nodes[i].x;

        y += nodes[i].y;
        yx1 += nodes[i].y * nodes[i].x;
        yx2 += nodes[i].y * nodes[i].x * nodes[i].x;
        yx3 += nodes[i].y * nodes[i].x * nodes[i].x * nodes[i].x;
    }

    long double slau[4][6] = {
            {x0, x1, x2, x3, y      },
            {x1, x2, x3, x4, yx1    },
            {x2, x3, x4, x5, yx2    },
            {x3, x4, x5, x6, yx3    },
    };

    long double a0 = 0;
    long double a1 = 0;
    long double a2 = 0;
    long double a3 = 0;

    //решаем слау

    //зануляем столбцы
    for (int i = 1; i < 4; ++i) {
        long double mnozh = slau[i][0] / slau[0][0];
        for (int j = 0; j < 6; ++j) {
            slau[i][j] -= mnozh * slau[0][j];
        }
        slau[i][0] = 0;
    }
    for (int i = 2; i < 4; ++i) {
        long double mnozh = slau[i][1] / slau[1][1];
        for (int j = 1; j < 6; ++j) {
            slau[i][j] -= mnozh * slau[1][j];
        }
        slau[i][1] = 0;
    }
    for (int i = 3; i < 4; ++i) {
        long double mnozh = slau[i][2] / slau[2][2];
        for (int j = 2; j < 6; ++j) {
            slau[i][j] -= mnozh * slau[2][j];
        }
        slau[i][2] = 0;
    }

    //считаем ответ
    a3 = (slau[3][4]) / slau[3][3];
    a2 = (slau[2][4] - a3 *  slau[2][3]) / slau[2][2];
    a1 = (slau[1][4] - a3 *  slau[1][3] - a2 *  slau[1][2]) / slau[1][1];
    a0 = (slau[0][4] - a3 *  slau[0][3] - a2 *  slau[0][2] - a1 * slau[0][1]) / slau[0][0];

    values.push_back(a0 + a1*x + a2*x*x + a3*x*x*x);
    return values;
}