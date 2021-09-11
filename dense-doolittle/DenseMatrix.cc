#include "DenseMatrix.hh"

#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

DenseMatrix::DenseMatrix(int n_rows, int n_cols)
    : n_rows(n_rows), n_cols(n_cols) {
  cout << "Regular Constructor" << endl;
  // in bytes per
  // https://www.cplusplus.com/reference/cstdlib/malloc/
  const int num_bytes = n_rows * n_cols * sizeof(double);
  mem = (double *)malloc(num_bytes);
  memset(mem, 0, num_bytes);
}

DenseMatrix::DenseMatrix(DenseMatrix &from_obj)
    : n_rows(from_obj.n_rows), n_cols(from_obj.n_cols) {
  cout << "Copy Constructor" << endl;
  const int num_bytes = n_rows * n_cols * sizeof(double);
  mem = (double *)malloc(num_bytes);
  memcpy(mem, from_obj.mem, num_bytes);
}

DenseMatrix::DenseMatrix(DenseMatrix &&from_obj)
    : n_rows(from_obj.n_rows), n_cols(from_obj.n_cols), mem(from_obj.mem) {
  cout << "Move Constructor r-value" << endl;
  from_obj.mem = nullptr;
  from_obj.n_cols = from_obj.n_rows = -1;
}

DenseMatrix &DenseMatrix::operator=(DenseMatrix &&from_obj) {
  cout << "Move Constructor r-value equals" << endl;
  if (&from_obj != this) {
    free(mem);
    mem = from_obj.mem;
    n_rows = from_obj.n_rows;
    n_cols = from_obj.n_cols;
  }
  return *this;
}

DenseMatrix &DenseMatrix::operator=(const DenseMatrix &from_obj) {
  cout << "Move constructor l-value equals" << endl;
  mem = from_obj.mem;
  n_rows = from_obj.n_rows;
  n_cols = from_obj.n_cols;
  return *this;
}

DenseMatrix::~DenseMatrix() {
  free(mem);
  mem = nullptr;
  n_rows = n_cols = -1;
}

int DenseMatrix::get_n_cols() const { return n_cols; }
int DenseMatrix::get_n_rows() const { return n_rows; }
double DenseMatrix::get_at(const int &i, const int &j) const {
  if (i >= 0 && i < n_rows) {
    if (j >= 0 && j < n_cols) {
      return this->mem[i * n_cols + j];
    } else {
      throw std::runtime_error(
          "Attempted to get invalid col index: " + to_string(j) +
          "from matrix with " + to_string(n_cols) + " cols.");
    }
  } else {
    throw std::runtime_error(
        "Attempted to get invalid row index: " + to_string(i) +
        " from matrix with " + to_string(n_rows) + " rows.");
  }
}
void DenseMatrix::set_at(const int &i, const int &j, const double &val) {
  if (i >= 0 && i < n_rows) {
    if (j >= 0 && j < n_cols) {
      this->mem[i * n_cols + j] = val;
    } else {
      throw std::runtime_error(
          "Attempted to set invalid col index: " + to_string(j) +
          " from matrix with " + to_string(n_cols) + " cols. Value was " +
          to_string(val) + ".");
    }
  } else {
    throw std::runtime_error(
        "Attempted to set invalid row index: " + to_string(i) +
        " from matrix with " + to_string(n_rows) + " rows. Value was " +
        to_string(val) + ".");
  }
}

ostream &operator<<(ostream &os, DenseMatrix const &m) {
  const int n_rows = m.get_n_rows();
  const int n_cols = m.get_n_cols();
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      os << m.get_at(i, j) << '\t';
    }
    os << "\n";
  }
  return os;
}
