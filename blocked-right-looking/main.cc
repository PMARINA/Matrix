#include "solution.cc"
#include <chrono>
#include<iostream>
using namespace std;
using namespace std::chrono;
int main()
{
  const int n = 1000;
  const int blockSize = 20;

  if (n % blockSize != 0)
    throw std::runtime_error("Expected blocksize to be a divisor of n.");

  double *matrix = parseFromMTX("Mat1000_1000.mtx", n);
  double **blockedMatrix = denseToDenseBlocked(matrix, n, blockSize);
  double ***results = initializeResults(n, blockSize);
  auto start = high_resolution_clock::now();
  double ***resultBlocked = lu_decompose(blockedMatrix, n / blockSize, blockSize, results);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Execution time: " << duration.count() << " us" << endl;
  double **resultDense = getResultDense(resultBlocked, n / blockSize, blockSize);
  // printMatrices(matrix, resultDense, n);
}