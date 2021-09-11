#include <ostream>
using std::ostream;
#ifndef MatrixHH

class Matrix {
 public:
  virtual int get_n_rows() const = 0;
  virtual int get_n_cols() const = 0;
  virtual double get_at(const int& i, const int& j) const = 0;
  virtual void set_at(const int& i, const int& j, const double& val) = 0;
};
#define MatrixHH

#endif
