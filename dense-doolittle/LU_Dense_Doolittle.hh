#include "DenseMatrix.hh"
#ifndef LU_Dense_DoolittleHH
using std::to_string;
class LU_Dense_Doolittle {
 private:
  DenseMatrix* upper = nullptr;
  DenseMatrix* lower = nullptr;
  DenseMatrix* input = nullptr;
  int n_rows = -1;
  int n_cols = -1;

 public:
  LU_Dense_Doolittle(DenseMatrix* dm);
  ~LU_Dense_Doolittle();
  void solve();
  DenseMatrix* get_upper();
  DenseMatrix* get_lower();
};
#define LU_Dense_DoolittleHH
#endif
