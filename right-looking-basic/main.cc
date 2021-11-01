#include <string.h>

#include <cstring>
#include <memory>

// #include "matrixGenerator.cc"
#include "matrixParser.cc"
#include "matrixPrinter.cc"

using std::cin;
using std::string;

double** ludecompose(double* m, const int n) {
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
  int index;
  double pivotInverse;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      index = i * n + j;  // Could replace with index++
      u[index] = m[index];
    }
    const double pivotInverse = 1 / u[i * (n + 1)];
    for (int j = i; j < n; j++) {
      index = j * n + i;  // Could replace with index += n
      l[index] = j == i ? 1 : pivotInverse * m[index];
    }
    for (int j = i + 1; j < n; j++) {
      for (int k = i + 1; k < n; k++) {
        m[j * n + k] -= l[j * n + i] * u[i * n + k];
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
  double* newMatrix = (double*)malloc(sizeof(double) * n * n);
  memcpy(newMatrix, matrix, n * n * sizeof(double));
  double** result = ludecompose(newMatrix, n);
  printMatrices(matrix, result, n);
  free(matrix);
  free(newMatrix);
  for (int i = 0; i < 2; i++) {
    free(result[i]);
  }
  free(result);
}