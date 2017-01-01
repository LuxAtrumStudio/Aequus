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
  if (a.size() != 3 || b.size() != 3) {
    pessum::logging::LogLoc(pessum::logging::LOG_WARNING,
                            "Vectors for cross product must have a length of 3",
                            logloc, "Cross");
  }
  if (a.size() == 3 && b.size() == 3) {
    output.push_back((a[1] * b[2]) - (b[1] * a[2]));
    output.push_back((b[0] * a[2]) - (a[0] * b[2]));
    output.push_back((a[0] * b[1]) - (b[0] * a[1]));
  }
  return (output);
}

double pessum::math::Determinate(std::vector<std::vector<double>> matrix) {
  double det = 0;
  if (matrix.size() != matrix[0].size()) {
    pessum::logging::LogLoc(
        pessum::logging::LOG_WARNING,
        "Matrix must be a square matrix for the determinate", logloc,
        "Determinate");
  } else {
    if (matrix.size() == 2) {
      return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    } else {
      for (int i = 0; i < matrix.size(); i++) {
        std::vector<std::vector<double>> submatrix;
        for (int j = 0; j < matrix.size(); j++) {
          if (j == i) {
            j++;
            if (j == matrix.size()) {
              break;
            }
          }
          std::vector<double> col;
          for (int k = 1; k < matrix[j].size(); k++) {
            col.push_back(matrix[j][k]);
          }
          submatrix.push_back(col);
        }
        det += (pow(-1, i) * matrix[i][0] * Determinate(submatrix));
        submatrix.clear();
      }
    }
  }
  return (det);
}

std::vector<std::vector<double>> pessum::math::MatrixMultipy(
    std::vector<std::vector<double>> a, std::vector<std::vector<double>> b) {
  std::vector<std::vector<double>> outputmatrix;
  if (a.size() != b[0].size()) {
    pessum::logging::LogLoc(pessum::logging::LOG_WARNING,
                            "Number of columns in first matrix must match "
                            "number of rows in seconed matrix",
                            logloc, "MatrixMultipy");
  }
  for (int j = 0; j < b.size(); j++) {
    std::vector<double> col;
    for (int i = 0; i < a[0].size(); i++) {
      double sum = 0;
      for (int k = 0; k < a.size() && k < b[0].size(); k++) {
        sum += a[k][i] * b[j][k];
      }
      col.push_back(sum);
    }
    outputmatrix.push_back(col);
  }
  return (outputmatrix);
}

std::vector<std::vector<double>> pessum::math::TransposeMatrix(
    std::vector<std::vector<double>> matrix) {
  std::vector<std::vector<double>> outputmatrix;
  for (int i = 0; i < matrix[0].size(); i++) {
    std::vector<double> col;
    for (int j = 0; j < matrix.size(); j++) {
      col.push_back(matrix[j][i]);
    }
    outputmatrix.push_back(col);
  }
  return (outputmatrix);
}

std::vector<std::vector<double>> pessum::math::ScalarMultipy(
    double a, std::vector<std::vector<double>> b) {
  for (int i = 0; i < b.size(); i++) {
    for (int j = 0; j < b[i].size(); j++) {
      b[i][j] *= a;
    }
  }
  return (b);
}

std::vector<std::vector<double>> pessum::math::SumMatrix(
    std::vector<std::vector<double>> a, std::vector<std::vector<double>> b) {
  std::vector<std::vector<double>> outputmatrix;
  if (a.size() != b.size() && a[0].size() != b[0].size()) {
    pessum::logging::LogLoc(pessum::logging::LOG_WARNING,
                            "For matrix addition one dimention has to match",
                            logloc, "SumMatrix");
  }
  if (a.size() == b.size() && a[0].size() == b[0].size()) {
    for (int i = 0; i < a.size(); i++) {
      std::vector<double> col;
      for (int j = 0; j < a[0].size(); j++) {
        col.push_back(a[i][j] + b[i][j]);
      }
      outputmatrix.push_back(col);
    }
  } else if (a.size() == b.size() && (a[0].size() == 1 || b[0].size() == 1)) {
    if (a[0].size() == 1) {
      for (int i = 0; i < b.size(); i++) {
        std::vector<double> col;
        for (int j = 0; j < b[0].size(); j++) {
          col.push_back(a[i][0] + b[i][j]);
        }
        outputmatrix.push_back(col);
      }
    } else if (b[0].size() == 1) {
      for (int i = 0; i < a.size(); i++) {
        std::vector<double> col;
        for (int j = 0; j < a[0].size(); j++) {
          col.push_back(a[i][j] + b[i][0]);
        }
        outputmatrix.push_back(col);
      }
    }
  } else if (a[0].size() == b[0].size() && (a.size() == 1 || b.size() == 1)) {
    if (a.size() == 1) {
      for (int i = 0; i < b.size(); i++) {
        std::vector<double> col;
        for (int j = 0; j < b[0].size(); j++) {
          col.push_back(a[0][j] + b[i][j]);
        }
        outputmatrix.push_back(col);
      }
    } else if (b.size() == 1) {
      for (int i = 0; i < a.size(); i++) {
        std::vector<double> col;
        for (int j = 0; j < a[0].size(); j++) {
          col.push_back(a[i][j] + b[0][j]);
        }
        outputmatrix.push_back(col);
      }
    }
  }
  return (outputmatrix);
}

std::vector<std::vector<double>> pessum::math::DiffMatrix(
    std::vector<std::vector<double>> a, std::vector<std::vector<double>> b) {
  std::vector<std::vector<double>> outputmatrix;
  if (a.size() != b.size() && a[0].size() != b[0].size()) {
    pessum::logging::LogLoc(pessum::logging::LOG_WARNING,
                            "For matrix subtraction one dimention has to match",
                            logloc, "SumMatrix");
  }
  if (a.size() == b.size() && a[0].size() == b[0].size()) {
    for (int i = 0; i < a.size(); i++) {
      std::vector<double> col;
      for (int j = 0; j < a[0].size(); j++) {
        col.push_back(a[i][j] - b[i][j]);
      }
      outputmatrix.push_back(col);
    }
  } else if (a.size() == b.size() && (a[0].size() == 1 || b[0].size() == 1)) {
    if (a[0].size() == 1) {
      for (int i = 0; i < b.size(); i++) {
        std::vector<double> col;
        for (int j = 0; j < b[0].size(); j++) {
          col.push_back(a[i][0] - b[i][j]);
        }
        outputmatrix.push_back(col);
      }
    } else if (b[0].size() == 1) {
      for (int i = 0; i < a.size(); i++) {
        std::vector<double> col;
        for (int j = 0; j < a[0].size(); j++) {
          col.push_back(a[i][j] - b[i][0]);
        }
        outputmatrix.push_back(col);
      }
    }
  } else if (a[0].size() == b[0].size() && (a.size() == 1 || b.size() == 1)) {
    if (a.size() == 1) {
      for (int i = 0; i < b.size(); i++) {
        std::vector<double> col;
        for (int j = 0; j < b[0].size(); j++) {
          col.push_back(a[0][j] - b[i][j]);
        }
        outputmatrix.push_back(col);
      }
    } else if (b.size() == 1) {
      for (int i = 0; i < a.size(); i++) {
        std::vector<double> col;
        for (int j = 0; j < a[0].size(); j++) {
          col.push_back(a[i][j] - b[0][j]);
        }
        outputmatrix.push_back(col);
      }
    }
  }
  return (outputmatrix);
}

void pessum::math::DisplayVector(std::vector<double> a) {
  std::string vec = "<";
  for (int i = 0; i < a.size() - 1; i++) {
    vec += ReduceDouble(a[i]) + ",";
  }
  vec += ReduceDouble(a[a.size() - 1]);
  vec += "> ";
  pessum::logging::LogLoc(pessum::logging::LOG_DATA, vec, logloc,
                          "DisplayVector");
}

void pessum::math::DisplayMatrix(std::vector<std::vector<double>> matrix) {
  std::string mat = "[";
  for (int i = 0; i < matrix[0].size(); i++) {
    mat += "[";
    for (int j = 0; j < matrix.size() - 1; j++) {
      mat += ReduceDouble(matrix[j][i]) + ",";
    }
    mat += ReduceDouble(matrix[matrix.size() - 1][i]) + "]";
  }
  mat += "]";
  pessum::logging::LogLoc(pessum::logging::LOG_DATA, mat, logloc,
                          "DisplayMatrix");
}

std::string pessum::math::ReduceDouble(double a) {
  std::string output = std::to_string(a);
  for (int i = output.size() - 1;
       i > 0 && (output[i] == '0' || output[i] == '.'); i--) {
    if (output[i] == '.') {
      output.pop_back();
      break;
    }
    output.pop_back();
  }
  return (output);
}
