#include <vector>
#include <functional>

struct vect_t{
    std::vector<long double> vect;
    long double t;
};

std::vector<long double> solveSLAU(std::vector<std::vector<long double>> matrix);
std::vector<long double> solveSNAU(std::vector<long double> start, std::function<std::vector<long double>(std::vector<long double>)> snau, std::function<std::vector<std::vector<long double>>(std::vector<long double>)> snauJ, long double e1, long double e2, int maxIter);

std::vector<vect_t> eulerExplicit(vect_t start, long double maxTime, long double eps_i, long double tau_max, std::function<std::vector<long double>(vect_t)> rhs);
std::vector<vect_t> eulerNonExplicit(vect_t start, long double maxTime, long double eps_i, long double tau_min, long double tau_max, std::function<std::vector<long double>(vect_t)> rhs, std::function<std::vector<std::vector<long double>>(vect_t)> rhsJ);
std::vector<vect_t> shikhman(vect_t start, long double maxTime, long double eps_i, long double tau_min, long double tau_max, std::function<std::vector<long double>(vect_t)> rhs, std::function<std::vector<std::vector<long double>>(vect_t)> rhsJ);