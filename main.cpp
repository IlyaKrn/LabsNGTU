#include "include/SLAU.h"
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char** argv) {


    auto matrix = getInterpolationMatrix(3, 1, 0, 0, 0, [](long double x) -> long double {
        return 0;
    });
    cout << getLambdaStep(matrix) << endl;
    cout << getLambdaBackIter(matrix) << endl;

}