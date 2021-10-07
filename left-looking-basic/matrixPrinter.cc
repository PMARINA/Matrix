#include <cmath>
#include <iostream>
using std::cout;
using std::endl;

void printMatrices(double *original, double **results,
                    int pivot_size) {
  double *l = (double *)results[0];
  double *u = (double *)results[1];
  
  cout << "L was " << l <<endl;
  cout << "U was " << u <<endl;

  int n = pivot_size;

  cout << "Original Matrix:\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << original[i * pivot_size + j] << "\t";
    }
    cout << "\n";
  }

  cout << "Lower Matrix:\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << l[i * pivot_size + j] << "\t";
    }
    cout << "\n";
  }
  cout << "\n\nUpper Matrix:\n";

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << u[i * pivot_size * j] << "\t";
    }
    cout << "\n";
  }
  cout << "\n\n" << endl;
}