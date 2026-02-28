#include <vector>
#include <functional>

std::vector<long double> solveSLAU(std::vector<std::vector<long double>> matrix);
std::vector<std::vector<long double>> getInterpolationMatrix(int n, long double h, long double x0, long double U0, long double Un, std::function<long double(long double)> f);

long double norm(std::vector<long double> v);
long double scalar(std::vector<long double> v1, std::vector<long double> v2);
std::vector<long double> normed(std::vector<long double> v);
long double getLambdaStep(std::vector<std::vector<long double>> matrix);
long double getLambdaBackIter(std::vector<std::vector<long double>> matrix);