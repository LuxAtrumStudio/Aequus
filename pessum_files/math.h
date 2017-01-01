#ifndef PESSUM_FILES_MATH_H_
#define PESSUM_FILES_MATH_H_
#include <string>
#include <vector>
#include "pessum_core.h"
namespace pessum {
namespace math {
extern int logloc;
void InitializeMath();
// Vector Functions
double Dot(std::vector<double> a, std::vector<double> b);
std::vector<double> Cross(std::vector<double> a, std::vector<double> b);
// Matrix Functions
double Determinate(std::vector<std::vector<double>> matrix);
std::vector<std::vector<double>> MatrixMultipy(
    std::vector<std::vector<double>> a, std::vector<std::vector<double>> b);
std::vector<std::vector<double>> TransposeMatrix(
    std::vector<std::vector<double>> matrix);
std::vector<std::vector<double>> ScalarMultipy(
    double a, std::vector<std::vector<double>> b);
std::vector<std::vector<double>> SumMatrix(std::vector<std::vector<double>> a,
                                           std::vector<std::vector<double>> b);
std::vector<std::vector<double>> DiffMatrix(std::vector<std::vector<double>> a,
                                            std::vector<std::vector<double>> b);
// Display Functions
void DisplayVector(std::vector<double> a);
void DisplayMatrix(std::vector<std::vector<double>> a);
std::string ReduceDouble(double a);
}
}
#endif
