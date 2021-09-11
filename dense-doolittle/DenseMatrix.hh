#include <ostream>

#include "Matrix.hh"
using std::ostream;
#ifndef DenseMatrixHH

class DenseMatrix : public Matrix {
 private:
  int n_rows;
  int n_cols;
  double* mem;

 public:
  // Standard Constructor
  DenseMatrix(int n_rows, int n_cols);

  // Copy Constructor
  DenseMatrix(DenseMatrix& from_obj);

  // Move Constructor
  DenseMatrix(DenseMatrix&& from_obj);

  // Move Assignment Operator with rvalue
  DenseMatrix& operator=(DenseMatrix&& from_obj);

  // Move Assignment Operator with lvalue
  DenseMatrix& operator=(const DenseMatrix& from_obj);

  // Destructor
  ~DenseMatrix();

  int get_n_rows() const;
  int get_n_cols() const;
  double get_at(const int& i, const int& j) const;
  void set_at(const int& i, const int& j, const double& val);
};
ostream& operator<<(ostream& os, DenseMatrix const& m);
#define DenseMatrixHH
#endif
