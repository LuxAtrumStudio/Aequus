#ifndef PESSUM_FILES_MATRIXMATH_H_
#define PESSUM_FILES_MATRIXMATH_H_
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
std::vector<double> ScalarMultiply(double a, std::vector<double> b);
std::vector<double> Sum(std::vector<double> a, std::vector<double> b);
std::vector<double> Diff(std::vector<double> a, std::vector<double> b);
std::vector<double> Product(std::vector<double> a, std::vector<double> b);
double Total(std::vector<double> a);
// Matrix Functions
double Determinate(std::vector<std::vector<double>> matrix);
std::vector<std::vector<double>> MatrixMultiply(
    std::vector<std::vector<double>> a, std::vector<std::vector<double>> b);
std::vector<std::vector<double>> TransposeMatrix(
    std::vector<std::vector<double>> matrix);
std::vector<std::vector<double>> ScalarMultiplyMatrix(
    double a, std::vector<std::vector<double>> b);
std::vector<std::vector<double>> SumMatrix(std::vector<std::vector<double>> a,
                                           std::vector<std::vector<double>> b);
std::vector<std::vector<double>> DiffMatrix(std::vector<std::vector<double>> a,
                                            std::vector<std::vector<double>> b);
std::vector<std::vector<double>> ProductMatrix(
    std::vector<std::vector<double>> a, std::vector<std::vector<double>> b);
std::vector<std::vector<double>> DivMatrix(std::vector<std::vector<double>> a,
                                           std::vector<std::vector<double>> b);
std::vector<std::vector<double>> DotMatrix(std::vector<std::vector<double>> a);
// Display Functions
void DisplayVector(std::vector<double> a);
void DisplayMatrix(std::vector<std::vector<double>> a);
void DisplayMatrixSize(std::vector<std::vector<double>> a);
std::string ReduceDouble(double a);
}
}
#endif
