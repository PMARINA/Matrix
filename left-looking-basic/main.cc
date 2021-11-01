#include <string.h>

#include <cstring>
#include <memory>

// #include "matrixGenerator.cc"
#include "matrixParser.cc"
#include "matrixPrinter.cc"

using std::cin;
using std::string;

double** ludecompose(const double* m, const int n) {
  double** results = (double**)malloc(sizeof(double*) * 2);
  double* l = (double*)malloc(n * n * sizeof(double));
  double* u = (double*)malloc(n * n * sizeof(double));
  memset(l, 0, n * n * sizeof(double));
  memset(u, 0, n * n * sizeof(double));
  results[0] = l;
  results[1] = u;

  // For caching the current column from U12
  double* solvedUpper = (double*)malloc(sizeof(double) * n);
  double* solvedLower = (double*)malloc(sizeof(double) * n);

  for (int j = 0; j < n; j++) {
    // Step 1
    solvedUpper[0] = m[j];
    solvedLower[j] = 1;
    if (j >= 2) {  // unnecessary if... remove later?
      for (int i = 1; i < j; i++) {
        double triangularSum = 0;
        for (int k = 0; k < i; k++) {
          triangularSum += l[i * n + k] * solvedUpper[k];
        }
        solvedUpper[i] = m[i * n + j] - triangularSum;
      }
    }

    // Step 2
    double invu22 = 1 / solvedUpper[0];
    if (j != 0) {
      double l21u12 = 0;
      for (int i = 0; i < j; i++) {
        l21u12 += l[j * n + i] * solvedUpper[i];
      }
      double u22 = m[j * (n + 1)] - l21u12;
      invu22 = 1 / u22;
      solvedUpper[j] = u22;
    }

    // Step 3
    for (int i = j + 1; i < n; i++) {
      double l31u12 = 0;
      if (j != 0) {
        if (j == 1) {
          l31u12 = l[i * n] * solvedUpper[0];
        } else {
          for (int k = 0; k < j; k++) {
            l31u12 += l[i * n + k] * solvedUpper[k];
          }
        }
      }
      solvedLower[i] = (m[i * n + j] - l31u12) * invu22;
    }

    // Copy the answers from the vectors into the answer matrices
    for (int i = 0; i < n; i++) {
      if (i < j) {
        u[i * n + j] = solvedUpper[i];
      } else if (i == j) {
        u[i * n + j] = solvedUpper[i];
        l[i * n + j] = solvedLower[i];
      } else {
        l[i * n + j] = solvedLower[i];
      }
    }
  }

  free(solvedUpper);
  free(solvedLower);

  return results;
}

int main() {
  const int n = 20;
  // double * matrix = genMatrix(n);
  double* matrix = parseFromMTX("Mat20_20.mtx", n);
  double** result = ludecompose(matrix, n);
  printMatrices(matrix, result, n);
  free(matrix);
  for (int i = 0; i < 2; i++) {
    free(result[i]);
  }
  free(result);
}