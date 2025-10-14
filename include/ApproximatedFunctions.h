#pragma once
#include <vector>
#include <string>


struct node {
    long double x;
    long double y;
};

std::vector<node> getNodes(std::string filePath);

std::vector<long double> minSquaresApproximation(long double x, std::vector<node> nodes);