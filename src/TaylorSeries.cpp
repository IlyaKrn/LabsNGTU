#include "../include/TaylorSeries.h"
#include <cmath>


//вычисление частичной суммы ряда Тейлора с приближением в x0 для точки x
float taylorSerial(float x, float x0, float k, int members){
    //общий результат
    float result = 0;
    for(int n = 0; n < members; n++){

        //считаем член ряда
        float memberValue = (n % 2 == 0) ? sin(k*x0) : cos(k*x0);      //чередование производных sin и cos
        memberValue *= (n % 4 == 0 || (n - 1) % 4 == 0) ? 1 : -1;             //чередование знака через 2 члена (cos' = -sin)
        memberValue *= pow(k, n) * pow(x - x0, n);                //k по правилам сложной ф-и. (x-x0)^n по формуле

        //считаем факториал и делим на него по формуле
        int fact = 1;
        for (int j = 1; j <= n; ++j) {
            fact *= j;
        }
        memberValue /= fact;
        //добавляем вычисленный член к частичной сумме
        result += memberValue;

    }
    return result;
}
