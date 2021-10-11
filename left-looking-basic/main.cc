
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
  double* sumLowerRows = (double*) malloc(sizeof(double) * n);
  memset(sumLowerRows, 0, sizeof(double)*n);
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
    cout << "upper PIVOT SUM START = " << upperPivotSum << endl;
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
        // cout << "i: " << i << "\tj: " << j << endl;
        solvedUpper[i] = thisSolution;
  
        // Perform the addition/product for step 2 as we compute the necessary
        // elements. Use it while it's in register?
        // cout << "L[" << j + 1 << ", " << i+1 -1<< "] = " << l[j * n + i-1] << endl;
        upperPivotSum += l[j * n + i] * thisSolution;
        cout << "upper PIVOT SUM += " << l[j * n + i] * thisSolution << endl;
      }
      // cout << "jn = " << j*n << endl;
      if (j != n-1)upperPivotSum += l[(j)*n + 1] * solvedUpper[j-1]; 
      cout << "UPPER PIVOT SUM = " << upperPivotSum<<endl;
      
    }

    double u22 = 0;

    if (j == 0) {
      u22 = m[0];
    }
    // Step 2: Solve the single diagonal element of U22
    if (j != 0) {
      u22 = m[j * n + j] - upperPivotSum;
      cout << "A = " << m[j*n+j] << endl;
      cout << "U22 = " << u22 <<endl << endl;
      u[j * n + j] = u22;
    }
    solvedUpper[j] = u22;
    const double invU22 = 1 / u22;
    // Step 3: Solve the lower matrix
    sumLowerRows[j] += 1;
    for (int i = j+1; i < n; i++) {
      double thisSolution = 0;
      if(j == 2 && i==3){
        cout <<"test"<<endl<<endl<<endl<<endl<<endl << "u22: " << u22<<endl;;
      }
      double sumL31U12Product = 0;
      if (j != 0) {
         double u12 = 0;
        if (j == 1){
          // U12 is a single value
          u12 = solvedUpper[0];
          sumL31U12Product = sumLowerRows[i] * u12;
        } else {
          u12 = solvedUpper[i-j-1];
        }
         double l31 = 0;
        if (j == (n-2)){
          // L31 is a single row sum
          l31 = sumLowerRows[n-1];
        } else {
          l31 = sumLowerRows[i];
        }
        cout << "Solved Upper [" << i-j-1 << "] = " << u12 << endl;
        cout << "l31 = " << l31 << endl;
        sumL31U12Product = l31 * u12;//(i - 1) * n + k
        cout << "sum L31U12 Product = " << sumL31U12Product <<endl;
        cout << "SumLowerRows[" << i <<"] = " << sumLowerRows[i] <<endl;
        cout << "A[" << i-j+2 << ", " << j+1 << "] = " << m[(i - j+1) * n + j] << endl;
        thisSolution = (m[(i - j+1) * n + j] - sumL31U12Product) * invU22;
      } else {
        thisSolution = (m[(i - j) * n + j] - sumL31U12Product) * invU22;
      }
      
      // cout << "L[" << i + 1 << ", " << j + 1 << "] = " << thisSolution << endl<<endl;
      l[i * n + j] = thisSolution;
      sumLowerRows[i] += thisSolution;
    }
    // cout << "End of solution iteration/column" << endl;
    // printMatrices((double*)m, results, 4);
    
  }
  // free(solvedUpper);
  // free(sumLowerRows)

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