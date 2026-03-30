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
    vector<vect_t> result = {start};
    vect_t curYktLast = {start.vect, start.t - tau_min};
    vect_t curYkt = start;
    vect_t curYktNext = start;
    long double tauk = tau_min;
    while (curYkt.t <= maxTime){
        curYktNext.t = curYkt.t + tauk;


        auto snau = [=](vector<long double> cur){
            vector<long double> res = rhs({cur, curYktNext.t});
            for (int i = 0; i < res.size(); ++i) {
                res[i] = cur[i] - curYkt.vect[i] - tauk * res[i];
            }
            return res;
        };
        auto snauJ = [=](vector<long double> cur){
            vector<vector<long double>> res = rhsJ({cur, curYktNext.t});
            for (int i = 0; i < res.size(); ++i) {
                for (int j = 0; j < res.size(); ++j) {
                    res[i][j] = 1 - tauk * res[i][j];
                }
            }
            return res;
        };

        curYktNext.vect = solveSNAU(curYktNext.vect, snau, snauJ, 1e-3, 1e-3, 1000);


        bool isOk = true;
        vector<long double> eps_ik = {};
        for (int i = 0; i < curYkt.vect.size(); ++i) {
            eps_ik.push_back(- (tauk / (tauk + curYkt.t - curYktLast.t))
                             * (curYktNext.vect[i] - curYkt.vect[i]
                                - ( tauk / (curYkt.t - curYktLast.t)) *
                                  (curYkt.vect[i] - curYktLast.vect[i])
                             ));
            if (abs(eps_ik[i]) > eps_i){
                isOk = false;
                break;
            }
        }
        if (!isOk){
            tauk = tauk / 2;
            curYktNext = curYkt;
            continue;
        }

        vector<long double> tausNext = {};
        for (int i = 0; i < curYktNext.vect.size(); ++i) {
            tausNext.push_back(sqrt(eps_i/abs(eps_ik[i]))*tauk);
        }

        long double tauNext = tausNext[0];
        for (int i = 0; i < tausNext.size(); ++i) {
            if(tausNext[i] < tauNext)
                tauNext = tausNext[i];
        }

        if (tauNext > tau_max)
            tauNext = tau_max;
        result.push_back(curYktNext);

        curYktLast = curYkt;
        curYkt = curYktNext;
        tauk = tauNext;
    }

    return result;
}

vector<vect_t> shikhman(vect_t start, long double maxTime, long double eps_i, long double tau_min, long double tau_max, function<vector<long double>(vect_t)> rhs, function<vector<vector<long double>>(vect_t)> rhsJ){
    vector<vect_t> result = {start};
    vect_t curYktLast = {start.vect, start.t - tau_min};
    vect_t curYkt = start;
    vect_t curYktNext = start;
    vect_t curYktLastLast = start;
    long double tauk = tau_min;

    int eulerIter = 0;
    while (curYkt.t <= maxTime && eulerIter < 2){
        cout << "gg" << endl;
        eulerIter++;
        curYktNext.t = curYkt.t + tauk;
        auto snau = [=](vector<long double> cur){
            vector<long double> res = rhs({cur, curYktNext.t});
            for (int i = 0; i < res.size(); ++i) {
                res[i] = cur[i] - curYkt.vect[i] - tauk * res[i];
            }
            return res;
        };
        auto snauJ = [=](vector<long double> cur){
            vector<vector<long double>> res = rhsJ({cur, curYktNext.t});
            for (int i = 0; i < res.size(); ++i) {
                for (int j = 0; j < res.size(); ++j) {
                    res[i][j] = 1 - tauk * res[i][j];
                }
            }
            return res;
        };
        curYktNext.vect = solveSNAU(curYktNext.vect, snau, snauJ, 1e-3, 1e-3, 1000);
        bool isOk = true;
        vector<long double> eps_ik = {};
        for (int i = 0; i < curYkt.vect.size(); ++i) {
            eps_ik.push_back(- (tauk / (tauk + curYkt.t - curYktLast.t))
                             * (curYktNext.vect[i] - curYkt.vect[i]
                                - ( tauk / (curYkt.t - curYktLast.t)) *
                                  (curYkt.vect[i] - curYktLast.vect[i])
                             ));
            if (abs(eps_ik[i]) > eps_i){
                isOk = false;
                break;
            }
        }
        if (!isOk){
            tauk = tauk / 2;
            curYktNext = curYkt;
            continue;
        }
        vector<long double> tausNext = {};
        for (int i = 0; i < curYktNext.vect.size(); ++i) {
            tausNext.push_back(sqrt(eps_i/abs(eps_ik[i]))*tauk);
        }
        long double tauNext = tausNext[0];
        for (int i = 0; i < tausNext.size(); ++i) {
            if(tausNext[i] < tauNext)
                tauNext = tausNext[i];
        }
        if (tauNext > tau_max)
            tauNext = tau_max;
        result.push_back(curYktNext);
        curYktLastLast = curYktLast;
        curYktLast = curYkt;
        curYkt = curYktNext;
        tauk = tauNext;
    }

    while (curYkt.t <= maxTime){
        curYktNext.t = curYkt.t + tauk;

        long double a1 = -tauk*tauk/((curYkt.t - curYktLast.t)*(2*tauk + curYkt.t - curYktLast.t));
        long double a0 = (tauk + curYkt.t - curYktLast.t)*(tauk + curYkt.t - curYktLast.t)/((curYkt.t - curYktLast.t)*(2*tauk + curYkt.t - curYktLast.t));
        long double b0 = (tauk*(tauk + curYkt.t - curYktLast.t))/(2*tauk + curYkt.t - curYktLast.t);

        auto snau = [=](vector<long double> cur){
            vector<long double> res = rhs({cur, curYktNext.t});
            for (int i = 0; i < res.size(); ++i) {
                res[i] = cur[i] - a1 * curYktLast.vect[i] - a0 * curYkt.vect[i] - b0 * res[i];
            }
            return res;
        };
        auto snauJ = [=](vector<long double> cur){
            vector<vector<long double>> res = rhsJ({cur, curYktNext.t});
            for (int i = 0; i < res.size(); ++i) {
                for (int j = 0; j < res.size(); ++j) {
                    res[i][j] = 1 - b0 * res[i][j];
                }
            }
            return res;
        };

        curYktNext.vect = solveSNAU(curYktNext.vect, snau, snauJ, 1e-3, 1e-3, 1000);


        bool isOk = true;
        vector<long double> eps_ik = {};
        for (int i = 0; i < curYkt.vect.size(); ++i) {
            long double u = 6*(
                curYktNext.vect[i]/(tauk*(tauk+curYkt.t-curYktLast.t)*(tauk+curYkt.t-curYktLast.t+curYktLast.t-curYktLastLast.t))-
                curYkt.vect[i]/(tauk*(curYkt.t-curYktLast.t)*(curYkt.t-curYktLast.t+curYktLast.t-curYktLastLast.t))+
                curYktLast.vect[i]/((curYkt.t-curYktLast.t)*(curYktLast.t-curYktLastLast.t)*(tauk+curYkt.t-curYktLast.t))-
                curYktLastLast.vect[i]/((curYktLast.t-curYktLastLast.t)*(curYkt.t-curYktLast.t+curYktLast.t-curYktLastLast.t)*(tauk+curYkt.t-curYktLast.t+curYktLast.t-curYktLastLast.t))
            );
            long double R = tauk*tauk*(tauk+curYkt.t-curYktLast.t)*(tauk+curYkt.t-curYktLast.t)/(6*((2*tauk+curYkt.t-curYktLast.t)))*u;
            eps_ik.push_back(R);
            if (abs(eps_ik[i]) > eps_i){
                isOk = false;
                break;
            }
        }
        if (!isOk){
            tauk = tauk / 2;
            curYktNext = curYkt;
            continue;
        }

        vector<long double> tausNext = {};
        for (int i = 0; i < curYktNext.vect.size(); ++i) {
            tausNext.push_back(sqrt(eps_i/abs(eps_ik[i]))*tauk);
        }

        long double tauNext = tausNext[0];
        for (int i = 0; i < tausNext.size(); ++i) {
            if(tausNext[i] < tauNext)
                tauNext = tausNext[i];
        }

        if (tauNext > tau_max)
            tauNext = tau_max;
        result.push_back(curYktNext);

        curYktLastLast = curYktLast;
        curYktLast = curYkt;
        curYkt = curYktNext;
        tauk = tauNext;
    }

    return result;
}


