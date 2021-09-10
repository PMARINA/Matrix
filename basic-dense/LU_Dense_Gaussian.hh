#include "DenseMatrix.hh"
#ifndef LU_Dense_GaussianHH
using std::to_string;
class LU_Dense_Gaussian {
 private:
  DenseMatrix* upper = nullptr;
  DenseMatrix* lower = nullptr;
  DenseMatrix* input = nullptr;
  int n_rows = -1;
  int n_cols = -1;

 public:
  LU_Dense_Gaussian(DenseMatrix* dm);
  void solve();
  DenseMatrix* get_upper();
  DenseMatrix* get_lower();
};
#define LU_Dense_GaussianHH
#endif
