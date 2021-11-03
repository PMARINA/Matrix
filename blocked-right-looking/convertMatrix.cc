#include <memory>
// #include "matrixParser.cc"
// #include "matrixPrinter.cc"
double **denseToDenseBlocked(double *dense, int dimN, int blockSize) {
  int n = blockSize;
  int numBlocks = dimN / blockSize;
  if (numBlocks * blockSize != dimN) return nullptr;

  double **ret = (double **)malloc(numBlocks * numBlocks * sizeof(double *));

  for (int i = 0; i < numBlocks; i++) {
    for (int j = 0; j < numBlocks; j++) {
      double *m = (double *)malloc(blockSize * blockSize * sizeof(double));
      ret[i * numBlocks + j] = m;
      for (int i_inner = 0; i_inner < blockSize; i_inner++) {
        for (int j_inner = 0; j_inner < blockSize; j_inner++) {
          int i_effective = i_inner + i * blockSize;
          int j_effective = j_inner + j * blockSize;
          int indexOfOriginal = i_effective * dimN + j_effective;
          m[i_inner * blockSize + j_inner] = dense[indexOfOriginal];
        }
      }
    }
  }
  return ret;
}

double *blockedToDense(double **blocked, int numBlocks, int blockSize) {
  double *converted = (double *)malloc(sizeof(double) * blockSize * numBlocks *
                                       blockSize * numBlocks);
  for (int i = 0; i < numBlocks; i++) {
    for (int j = 0; j < numBlocks; j++) {
      for (int i_in = 0; i_in < blockSize; i_in++) {
        for (int j_in = 0; j_in < blockSize; j_in++) {
          const int outer_index =
              (blockSize * i + i_in) * numBlocks * blockSize + blockSize * j +
              j_in;
          converted[outer_index] =
              blocked[i * numBlocks + j][i_in * blockSize + j_in];
        }
      }
    }
  }
  return converted;
}

// Code to verify if the conversion is working...
// Also a demo of how to use it
#if 0
int main()
{
    const int n = 20;
    const int blockSize = 4;
    double *matrix = parseFromMTX("Mat20_20.mtx", n);
    double **blockedMatrix = denseToDenseBlocked(matrix, n, blockSize);
    double *backMatrix = blockedToDense(blockedMatrix, n / blockSize, blockSize);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i * n + j] != backMatrix[i * n + j])
            {
                cout << "Failed: " << i << ", " << j << endl;
            }
            else{
                cout << ".";
            }
        }
    }
    cout << endl;
    free(matrix);
    free(backMatrix);
    for(int i = 0; i<n/blockSize*n/blockSize; i++){
        free(blockedMatrix[i]);
    }
    free(blockedMatrix);
}
#endif