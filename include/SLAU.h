#include <vector>
#include <functional>

std::vector<long double> solveSLAU(std::vector<std::vector<long double>> matrix);
std::vector<std::vector<long double>> getInterpolationMatrix(int n, long double h, long double x0, long double U0, long double Un, std::function<long double(long double)> f);
