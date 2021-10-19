#include "LU_Dense_Gaussian.hh"

#include <iostream>
using std::cout;
using std::endl;
LU_Dense_Gaussian::LU_Dense_Gaussian(DenseMatrix *dm)
    : input(dm), n_rows(dm->get_n_rows()), n_cols(dm->get_n_cols()) {
  input = dm;
  if (n_rows != n_cols)
    throw std::runtime_error(
        "This method only works on square matrices, received matrix with "
        "dimensions " +
        to_string(n_rows) + " x " + to_string(n_cols));
}
void LU_Dense_Gaussian::solve() {
  upper = new DenseMatrix(*input);
  lower = new DenseMatrix(n_rows, n_cols);
// perform elimination & stuff
#define u (*upper)
#define l (*lower)
#define in (*input)
  for (int i = 0; i < n_rows; i++) {
    // Convention is that the lower matrix contains the diagonal of 1's
    l.set_at(i, i, 1);
    for (int j = 0; j < i; j++) {
      // Eliminate the j'th item in the row
      double multiplication_factor = (-u.get_at(i, j)) / (u.get_at(j, j));
      // Row subtraction will 0 it out, so set manually to prevent roundoff
      // issues.
      u.set_at(i, j, 0);
      l.set_at(i, j, -multiplication_factor);
      // Perform row subtraction
      for (int k = j + 1; k < n_cols; k++) {
        const double val =
            u.get_at(i, k) + u.get_at(j, k) * multiplication_factor;
        u.set_at(i, k, val);
      }
    }
  }
}
DenseMatrix *LU_Dense_Gaussian::get_upper() {
  if (upper == nullptr) solve();
  return upper;
}
DenseMatrix *LU_Dense_Gaussian::get_lower() {
  if (lower == nullptr) solve();
  return lower;
}
