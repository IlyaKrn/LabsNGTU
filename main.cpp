#include <iostream>
#include <math.h>
#include "include/SLAU.h"

using namespace std;

int main(int argc, char** argv) {

    //начальные данные
    int k = 1;
    long double e1 = 1e-9;
    long double e2 = 1e-9;
    int maxIter = 1000;

    //приближение предыдущей итерации
    vector<long double> Xk = {1, -1};

    //нормы ошибок предыдущей итерации
    long double d2 = e2*2;
    long double d1 = e1*2;

    //начинаем итерации
    while (d1 > e1 || d2 > e2){
        k++;

        //если итераций слишком много, выходим с ошибкой
        if (k > maxIter){
            cout << "iteration limit error" << endl;
            break;
        }

        //получаем матрицу Якоби и вектор невязки
        vector<vector<long double>> Jk = getJacobean(Xk);
        vector<long double> Fk = getFuncErr(Xk);

        //решаем СЛАУ для нахождения дельты
        vector<long double> Dxk = solveSLAU({
            {Jk[0][0], Jk[0][1], -Fk[0]},
            {Jk[1][0], Jk[1][1], -Fk[1]},
            });


        //получаем следующее приближение
        vector<long double> Xk1 = {
                Xk[0] + Dxk[0],
                Xk[1] + Dxk[1],
        };

        //пересчитываем нормы
        d1 = 0;
        d2 = 0;
        for (int i = 0; i < Fk.size(); ++i) {
            if (d1 < Fk[i])
                d1 = Fk[i];
        }
        if(sqrt(Xk1[0]*Xk1[0] + Xk1[1]*Xk1[1]) < 1){
            for (int i = 0; i < Fk.size(); ++i) {
                long double tmp = Xk1[i] - Xk[i];
                if (d1 < tmp) {
                    d1 = tmp;
                }
            }
        }
        else {
            for (int i = 0; i < Fk.size(); ++i) {
                long double tmp = (Xk1[i] - Xk[i]) / Xk1[i];
                if (d1 < tmp) {
                    d1 = tmp;
                }
            }
        }

        //переходим в новому приближению
        Xk = Xk1;


    }


}