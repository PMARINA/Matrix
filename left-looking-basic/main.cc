
#include <string.h>

#include <cstring>
#include <memory>

#include "matrixGenerator.cc"
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
  double* solvedLower = (double*) malloc(sizeof(double) * n);
  // cout << "Everything should be 0 here " << endl;
  // printMatrices((double*)m, results, 4);
  // cout << "Starting computation" << endl;
  // Left looking, so we iterate by column, then by row!
  for (int j = 0; j < n; j++) {
    // The first row is the same as the original matrix
    const double fromOrig = m[j];
    u[j] = fromOrig;
    l[j * n + j] = 1;
    
    solvedUpper[0] = fromOrig;
    double upperPivotSum = (j == 0) ? 0 : l[n] * solvedUpper[j*n];
    if (j == 1){
      upperPivotSum += l[n] * solvedUpper[0];
    }
    // i < j to avoid solving 0s at bottom of upper matrix.
    // Don't run the loop if it's going to hit 1,1
    if (j >= 2){
      for (int i = 1; i < j; i++) {
        // Step 1: Solve for U21 through triangular solve
        double triangularSum = 0;
  
        for (int k = 0; k < i; k++)
          triangularSum += solvedUpper[k] * l[i * n + k];
  
        const double thisSolution = m[i * n + j] - triangularSum;
        u[i * n + j] = thisSolution;
        cout << "i: " << i << "\tj: " << j << endl;
        solvedUpper[i] = thisSolution;
  
        // Perform the addition/product for step 2 as we compute the necessary
        // elements. Use it while it's in register?
        upperPivotSum += l[j * n + i] * thisSolution;
      }
    }

    double u22 = 0;

    if (j == 0) {
      u22 = m[0];
    }
    // Step 2: Solve the single diagonal element of U22
    if (j != 0) {
      u22 = m[j * n + j] - upperPivotSum;
      u[j * n + j] = u22;
    }
    solvedUpper[j] = u22;
    const double invU22 = 1 / u22;
    // Step 3: Solve the lower matrix
    for (int i = j+1; i < n; i++) {
      if(j == 1 && i==2)
        cout <<"test"<<endl<<endl<<endl;
      double sumL31U12Product = 0;
      if (j != 0) {
        for (int k = 0; k < i; k++) {
          sumL31U12Product += l[(i - 1) * n + k] * solvedUpper[k];
        }
        cout << "sum L31U12 Product = " << sumL31U12Product <<endl;
      }
      const double thisSolution =
          (m[(i - j) * n + j] - sumL31U12Product) * invU22;
      cout << "L[" << i + 1 << ", " << j + 1 << "] = " << thisSolution << endl;
      l[i * n + j] = thisSolution;
    }
    // cout << "End of solution iteration/column" << endl;
    // printMatrices((double*)m, results, 4);
    
  }
  // free(solvedUpper);
  // free(solvedLower)

  return results;
}

int main() {
  const int n = 4;
  double* matrix = genMatrix(n);
  double** result = ludecompose(matrix, n);
  printMatrices(matrix, result, n);
  free(matrix);
  for (int i = 0; i < 2; i++) {
    free(result[i]);
  }
  free(result);
}