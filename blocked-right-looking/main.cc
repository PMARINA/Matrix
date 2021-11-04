#include <omp.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#define THREAD_NUM 4
#include "solution.cc"

using namespace std;
using namespace std::chrono;
int main() {
  omp_set_num_threads(
      THREAD_NUM);  // set number of threads in "parallel" blocks

  const int n = 10000;
  const int blockSize = 20;

  if (n % blockSize != 0)
    throw std::runtime_error("Expected blocksize to be a divisor of n.");

  double *matrix = parseFromMTX("Mat10000_10000.mtx", n);
  double **blockedMatrix = denseToDenseBlocked(matrix, n, blockSize);
  double ***results = initializeResults(n, blockSize);
  auto start = high_resolution_clock::now();
  double ***resultBlocked =
      lu_decompose(blockedMatrix, n / blockSize, blockSize, results);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Execution time: " << duration.count() << " us" << endl;
  double **resultDense;
}