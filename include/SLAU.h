#include "vector"

struct SLAU {
    int n;
    std::vector<std::vector<long double>> matrix;
};

void printSLAU(SLAU slau);
std::vector<SLAU> getSLAUs(std::string filename);
SLAU solveSLAU(SLAU slau);
std::vector<long double> answerSLAU(SLAU slau);