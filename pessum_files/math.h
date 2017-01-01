#ifndef PESSUM_FILES_MATH_H_
#define PESSUM_FILES_MATH_H_
#include <string>
#include <vector>
#include "pessum_core.h"
namespace pessum {
namespace math {
extern int logloc;
void InitializeMath();
double Dot(std::vector<double> a, std::vector<double> b);
std::vector<double> Cross(std::vector<double> a, std::vector<double> b);
double Determinate(std::vector<std::vector<double>> matrix);
std::vector<std::vector<double>> MatrixMultipy(
    std::vector<std::vector<double>> a, std::vector<std::vector<double>> b);
}
}
#endif
