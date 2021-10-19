#include "LU_Dense_Doolittle.hh"

#include "DenseMatrix.hh"

#define u (*upper)
#define l (*lower)
#define in (*input)
LU_Dense_Doolittle::LU_Dense_Doolittle(DenseMatrix *dm)
    : input(dm), n_rows(dm->get_n_rows()), n_cols(dm->get_n_cols()) {
  if (n_rows != n_cols) {
    throw std::runtime_error(
        "This method only works on square matrices, received matrix with "
        "dimensions " +
        to_string(n_rows) + " x " + to_string(n_cols));
  }
}
void LU_Dense_Doolittle::solve() {
  upper = new DenseMatrix(n_rows, n_cols);
  lower = new DenseMatrix(n_rows, n_cols);

  // copy the first row into upper
  for (int j = 0; j < n_cols; j++) {
    u.set_at(0, j, in.get_at(0, j));
  }

  // set the diagonal for lower
  for (int i = 0; i < n_rows; i++) {
    l.set_at(i, i, 1);
  }
  // Perform Doolittle
  for (int i = 1; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      if (j == 0) {
        double inserted_val = in.get_at(i, j) / u.get_at(j, j);
        l.set_at(i, j, inserted_val);
      } else {
        double orig_val = in.get_at(i, j);
        if (i <= j) {
          // Upper Matrix needs to be calculated
          double sum = 0;
          for (int k = 0; k < i; k++) {
            sum += (l.get_at(i, k) * u.get_at(k, j));
          }
          double inserted_val = orig_val - sum;
          u.set_at(i, j, inserted_val);
        } else {
          // Lower Matrix needs to be calculated
          double sum = 0;
          for (int k = 0; k < j; k++) {
            sum += (l.get_at(i, k) * u.get_at(k, j));
          }
          double inserted_val = (orig_val - sum) / u.get_at(j, j);
          l.set_at(i, j, inserted_val);
        }
      }
    }
  }
}
DenseMatrix *LU_Dense_Doolittle::get_upper() {
  if (upper == nullptr) solve();
  return upper;
};
DenseMatrix *LU_Dense_Doolittle::get_lower() {
  if (lower == nullptr) solve();
  return lower;
};
LU_Dense_Doolittle::~LU_Dense_Doolittle() {
  delete lower;
  delete upper;
}
