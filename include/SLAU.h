#include <vector>
#include <functional>

std::vector<long double> solveSLAU(std::vector<std::vector<long double>> matrix);
std::vector<long double> solveSNAU(std::vector<long double> start, std::function<std::vector<long double>(std::vector<long double>)> snau, std::function<std::vector<std::vector<long double>>(std::vector<long double>)> snauJ, long double e1, long double e2, int maxIter);