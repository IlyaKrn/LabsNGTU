#include <vector>
#include <functional>

//срез по времени
struct vect_t{
    std::vector<long double> X;
    std::vector<long double> U;
    long double t;
};

std::vector<long double> solveSLAU(std::vector<std::vector<long double>> matrix);

std::vector<vect_t> explicitSchema(std::function<long double(long double)> fi, std::function<long double(long double, long double)> f, std::function<long double(long double)> g1, std::function<long double(long double)> g2, long double a, long double T1, long double T2, long double X1, long double X2, int Tn);
std::vector<vect_t> nonExplicitSchema(std::function<long double(long double)> fi, std::function<long double(long double, long double)> f, std::function<long double(long double)> g1, std::function<long double(long double)> g2, long double a, long double T1, long double T2, long double X1, long double X2, int Tn);
