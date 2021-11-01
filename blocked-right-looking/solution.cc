#include <string.h>

#include <cstring>
#include <memory>

// #include "matrixGenerator.cc"
#include "matrixParser.cc"
#include "matrixPrinter.cc"
#include "convertMatrix.cc"

using std::cin;
using std::string;

double ***initializeResults(int nOverall, const int blockSize)
{
  const int numBlocks = nOverall / blockSize;
  const int blockSize_bytes = blockSize * blockSize * sizeof(double);
  double ***results = (double ***)malloc(sizeof(double **) * 2);
  double **l = (double **)malloc(sizeof(double *) * numBlocks * numBlocks);
  double **u = (double **)malloc(sizeof(double *) * numBlocks * numBlocks);
  results[0] = l;
  results[1] = u;

  double *currBlock = nullptr;
  for (int i = 0; i < 2; i++)
  {
    for (int o = 0; o < numBlocks * numBlocks; o++)
    {
      currBlock = (double *)malloc(blockSize_bytes);
      results[i][o] = currBlock;
      memset(currBlock, 0, blockSize_bytes);
    }
  }
  return results;
}

/**
 * @brief Solve type one blocks in right-looking-blocked
 *
 * We perform regular right-looking on a single-block, iteratively.
 * 
 * @param dstL The destination L matrix block, corresponding with M. Write-only
 * @param dstU The destination U matrix block, corresponding with M. Write-only
 * @param srcM The source data from M matrix. Read & Write - schur's complement
 * @param blockSize The width or height of a square block
 */
void solveTypeOne(double *dstL, double *dstU, double *srcM, const int blockSize)
{
  int index;
  double *&u = dstU;
  double *&m = srcM;
  double *&l = dstL;
  const int &n = blockSize;
  // Basic loop from unblocked
  for (int o = 0; o < n; o++)
  {
    // Copy the top row into u-matrix
    for (int j = o; j < n; j++)
    {
      index = o * n + j;
      u[index] = m[index];
    }
    // o*n+o -> o*(n+1)
    // Solve the lower matrix for that line
    const double pivotInverse = 1 / u[o * (n + 1)];
    for (int j = o; j < n; j++)
    {
      index = j * n + o; // Could replace with index += n
      l[index] = j == o ? 1 : pivotInverse * m[index];
    }
    // Perform Schur's complement on the remaining cells
    for (int j = o + 1; j < n; j++)
    {
      for (int k = o + 1; k < n; k++)
      {
        m[j * n + k] -= l[j * n + o] * u[o * n + k];
      }
    }
  }
}

/**
 * @brief Solve type two blocks of right-looking-blocked (left-vertical column)
 * 
 * @param dstL The L block being solved - write only
 * @param srcU The U block corresponding to the pivot block?
 * @param srcM The M block corresponding to the left block being solved
 * @param blockSize The width or height of a square block
 */
void solveTypeTwo(double *dstL, const double *srcU, double *srcM, const int &blockSize)
{
  int index;

  for(int o = 0; o<blockSize; o++){
    const double pivotInverse = 1/srcU[o*(blockSize + 1)];
    for(int i = 0; i < blockSize; i++){
      index = i*blockSize + o;
      dstL[index] = srcM[index] * pivotInverse;
    }

    for(int i = 0; i <blockSize; i++){
      for(int j = o + 1; j < blockSize; j++){
        srcM[i*blockSize + j] -= dstL[i*blockSize + o] * srcU[o*blockSize + j];
      }
    }
  }
}

/**
 * @brief Solve type three blocks of right-looking-blocked (top horizontal row)
 * 
 * @param dstU The U block being solved
 * @param srcL The L block corresponding to the pivot
 * @param srcM The M block corresponding to the top block being served
 * @param blockSize The width or height of a square block
 */
void solveTypeThree(double *dstU, double *srcL, double *srcM, const int &blockSize)
{
  int index;
  double *&u = dstU;
  double *&m = srcM;
  double *&l = srcL;
  const int &n = blockSize;
  // o is the row-offset from the top
  for (int o = 0; o < n; o++)
  {
    // Copy the top row into u-matrix
    for (int j = 0; j < n; j++)
    {
      index = o * n + j;
      u[index] = m[index];
    }
    // No need to solve the lower matrix, as we're strictly above the pivot
    // Perform Schur's complement on the remaining cells
    for (int j = o + 1; j < n; j++)
    {
      for (int k = 0; k < n; k++)
      {
        m[j * n + k] -= l[j * n + o] * u[o * n + k];
      }
    }
  }
}

/**
 * @brief Solve type four blocks in right-looking-blocked
 *
 * We perform schur's complement on a single-block, iteratively.
 * 
 * @param srcL The destination L matrix block, corresponding with left-most. read-only
 * @param srcU The destination U matrix block, corresponding with top-most. read-only
 * @param dstM The source data from M matrix. Read & Write - schur's complement
 * @param blockSize The width or height of a square block
 */
void solveTypeFour(double *&srcL, double *&srcU, double *dstM, const int blockSize)
{
  int index;
  double *&u = srcU;
  double *&m = dstM;
  double *&l = srcL;
  const int &n = blockSize;
  // Basic loop from unblocked
  for (int o = 0; o < n; o++)
  {
    // Perform Schur's complement on the remaining cells
    for (int j = 0; j < n; j++)
    {
      for (int k = 0; k < n; k++)
      {
        m[j * n + k] -= l[j * n + o] * u[o * n + k];
      }
    }
  }
}

double ***lu_decompose(double **blockedMatrix, const int &numBlocks, const int &blockSize, double*** results)
{
  double **l = results[0];
  double **u = results[1];
  for (int o = 0; o < numBlocks; o++)
  {
    solveTypeOne(l[o * (numBlocks + 1)], u[o * (numBlocks + 1)], blockedMatrix[o * (numBlocks + 1)], blockSize);
    for (int i = o + 1; i < numBlocks; i++)
    {
      solveTypeTwo(l[i * numBlocks + o], u[o * (numBlocks + 1)], blockedMatrix[i * numBlocks + o], blockSize);
    }
    for (int j = o + 1; j < numBlocks; j++)
    {
      solveTypeThree(u[o * numBlocks + j], l[o * (numBlocks + 1)], blockedMatrix[o * numBlocks + j], blockSize);
    }
    for (int i = o + 1; i < numBlocks; i++)
    {
      for (int j = o + 1; j < numBlocks; j++)
      {
        solveTypeFour(l[i * numBlocks + o], u[o*numBlocks + j], blockedMatrix[i * numBlocks + j], blockSize);
      }
    }
  }
  return results;
}

double **getResultDense(double ***resultsBlocked, int numBlocks, int blockSize)
{
  double **results = (double **)malloc(sizeof(double *) * 2);
  double *l = blockedToDense(resultsBlocked[0], numBlocks, blockSize);
  double *u = blockedToDense(resultsBlocked[1], numBlocks, blockSize);
  results[0] = l;
  results[1] = u;
  return results;
}
