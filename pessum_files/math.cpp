#include <math.h>
#include <string>
#include <vector>
#include "logging.h"
#include "math.h"
#include "pessum_core.h"

namespace pessum {
namespace math {
int logloc = 0;
}
}

void pessum::math::InitializeMath() {
  logloc = pessum::logging::AddLogLocation("pessum_files/math/");
}

double pessum::math::Dot(std::vector<double> a, std::vector<double> b) {
  if (a.size() != b.size()) {
    pessum::logging::LogLoc(pessum::logging::LOG_WARNING,
                            "Vectors for dot product must be the same length",
                            logloc, "Dot");
  }
  double sum = 0;
  for (int i = 0; i < a.size() && i < b.size(); i++) {
    sum += a[i] * b[i];
  }
  return (sum);
}

std::vector<double> pessum::math::Cross(std::vector<double> a,
                                        std::vector<double> b) {
  std::vector<double> output;
  if (a.size() != b.size()) {
    pessum::logging::LogLoc(pessum::logging::LOG_WARNING,
                            "Vectors for cross product must be the same legth",
                            logloc, "Cross");
  }
  return (output);
}

double pessum::math::Determinate(std::vector<std::vector<double>> matrix) {
  double det = 0;
  return (det);
}

std::vector<std::vector<double>> pessum::math::MatrixMultipy(
    std::vector<std::vector<double>> a, std::vector<std::vector<double>> b) {
  std::vector<std::vector<double>> outputmatrix;
  return (outputmatrix);
}
