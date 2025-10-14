#include "../include/ApproximatedFunctions.h"
#include <fstream>
#include <cmath>

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

    for (int i = 0; i < nodes.size(); ++i) {
        x0 += pow(nodes[i].x, 0);
        x1 += pow(nodes[i].x, 1);
        x2 += pow(nodes[i].x, 2);
        x3 += pow(nodes[i].x, 3);
        x4 += pow(nodes[i].x, 4);
        x5 += pow(nodes[i].x, 5);
        x6 += pow(nodes[i].x, 6);
        y += y;
    }

    long double a0 = 0;
    long double a1 = 0;
    long double a2 = 0;
    long double a3 = 0;

    //решаем слау




    values.push_back(a0 + a1*x + a2*x*x + a3*x*x*x);
    return values;
}