#include "../include/InterpolatedFunctions.h"
#include <fstream>

using namespace std;

vector<node> getNodes(string filePath){
    vector<node> nodes;
    ifstream file(filePath);
    long double x, y;
    while (file >> x >> y){
        nodes.push_back({x / 10, - y / 10});
    }
    return nodes;
}

vector<long double> linearInterpolation(long double x, vector<node> nodes){
    vector<long double> values;

    for (int i = 0; i < nodes.size() - 1; ++i){
        if (min(nodes[i].x, nodes[i + 1].x) <= x && max(nodes[i].x, nodes[i + 1].x) > x){
            values.push_back(((x - nodes[i].x) * (nodes[i + 1].y - nodes[i].y)) / (nodes[i + 1].x - nodes[i].x) + nodes[i].y);
        }
    }
    return values;
}

vector<long double> lagrangeInterpolation(long double x, vector<node> nodes){
    vector<long double> values;

    long double summValue = 0;
    for (int i = 0; i < nodes.size(); ++i) {
        long double proizv = 1;
        for (int j = 0; j < nodes.size(); ++j) {
            if(j != i && nodes[i].x != nodes[j].x){
                proizv *= (x - nodes[j].x) / (nodes[i].x - nodes[j].x);
            }
        }

        summValue += nodes[i].y * proizv;
    }
//    values.push_back(summValue);
    return values;
}

vector<long double> newtonInterpolation(long double x, vector<node> nodes){
    vector<long double> values;

    long double summValue = nodes[0].y;
    for (int i = 1; i < nodes.size(); ++i) {
        long double proizv = 1;
        for (int j = 0; j < i; ++j) {
            proizv *= x - nodes[j].x;
        }
        long double razdRaz = 0;
        for (int j = 0; j <= i; ++j) {
            long double znam = 1;
            for (int k = 0; k <= i; ++k) {
                if(j != k) {
                    znam *= nodes[j].x - nodes[k].x;
                }
            }
            razdRaz += nodes[j].y / znam;
        }

        summValue += proizv * razdRaz;
    }
//    values.push_back(summValue);
    return values;
}

vector<long double> splineInterpolation(long double x, vector<node> nodes){
    vector<long double> values;

    long double a = 0;
    long double b = 0;
    long double c = 0;
    long double d = 0;
    long double h = 0;


    for (int i = 0; i < nodes.size() - 1; ++i){
        long double aLast = a;
        long double bLast = b;
        long double cLast = c;
        long double dLast = d;
        long double hLast = h;

        a = nodes[i].y;

        if (i > 0) {
            h = nodes[i].x - nodes[i - 1].x;
            c = 0;
            d = (c - cLast) / (3 * h);
            b = (a - aLast) / h - h * (2 * cLast + c) / 3;
        }



        if (min(nodes[i].x, nodes[i + 1].x) <= x && max(nodes[i].x, nodes[i + 1].x) > x){
            values.push_back(a + b * (x - nodes[i].x) + c * (x - nodes[i].x) * (x - nodes[i].x) + d * (x - nodes[i].x) * (x - nodes[i].x) * (x - nodes[i].x));
        }
    }
    return values;
}