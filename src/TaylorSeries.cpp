#include "../include/TaylorSeries.h"
#include <cmath>


//вычисление частичной суммы ряда Тейлора с приближением в x0 для точки x
double taylorSerial(double x, double x0, double k, int members){
    //общий результат
    double result = 0;
    for(int n = 0; n < members; n++){

        //считаем член ряда
        double memberValue = (n % 2 == 0) ? sin(k*x0) : cos(k*x0);
        memberValue *= (n % 4 == 0 || (n - 1) % 4 == 0) ? 1 : -1;
        memberValue *= pow(k, n) * pow(x - x0, n);
        int fact = 1;
        for (int j = 1; j <= n; ++j) {
            fact *= j;
        }

        memberValue /= fact;
        result += memberValue;
    }
    return result;
}
