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

vector<long double> solveSNAU(vector<long double> start, function<vector<long double>(vector<long double>)> snau, function<vector<vector<long double>>(vector<long double>)> snauJ, long double e1, long double e2, int maxIter){
    int k = 0;
    vector<long double> Xk = start;
    long double d2 = e2+1;
    long double d1 = e1+1;
    while (d1 > e1 || d2 > e2){
        k++;
        if (k > maxIter)
            throw "iteration limit error!";
        vector<vector<long double>> Jk = snauJ(Xk);
        vector<long double> Fk = snau(Xk);
        vector<vector<long double>> slau = Jk;
        for (int i = 0; i < Jk.size(); ++i) {
            slau[i].push_back(-Fk[i]);
        }
        vector<long double> Dxk = solveSLAU(slau);
        vector<long double> Xk1;
        for (int i = 0; i < Xk.size(); ++i) {
            Xk1.push_back(Xk[i] + Dxk[i]);
        }
        d1 = 0;
        d2 = 0;
        for (int i = 0; i < Fk.size(); ++i) {
            if (d1 < abs(Fk[i]))
                d1 = abs(Fk[i]);
        }
        long double norm = 0;
        for (int i = 0; i < Xk1.size(); ++i) {
            norm += Xk1[i] * Xk1[i];
        }
        if(sqrt(norm) < 1){
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
        Xk = Xk1;
    }
    return Xk;
}

vector<vect_t> eulerExplicit(vect_t start, long double maxTime, long double eps_i, long double tau_max, function<vector<long double>(vect_t)> rhs){
    vector<vect_t> result = {start};
    vect_t curYkt = start;
    while (curYkt.t <= maxTime){
        vector<long double> f = rhs(curYkt);

        vector<long double> taus;
        for (int i = 0; i < f.size(); ++i) {
            taus.push_back(eps_i / (abs(f[i]) + eps_i / tau_max) );
        }
        long double tau = taus[0];
        for (int i = 0; i < taus.size(); ++i) {
            if(tau > taus[i])
                tau = taus[i];
        }

        for (int i = 0; i < curYkt.vect.size(); ++i) {
            curYkt.vect[i] += tau * f[i];
        }
        curYkt.t += tau;
        result.push_back(curYkt);
    }

    return result;
}

vector<vect_t> eulerNonExplicit(vect_t start, long double maxTime, long double eps_i, long double tau_min, long double tau_max, function<vector<long double>(vect_t)> rhs, function<vector<vector<long double>>(vect_t)> rhsJ){

}
