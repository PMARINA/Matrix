#include <memory>
#include <string.h>
double* genMatrix(const int n) {
  // My file parsing code works on windows but I need to figure out the
  // libraries for mac/linux. Will do eventually.
  if (n == 4) {
    double* m = (double*)malloc(sizeof(double) * n * n);
    memset(m, 0, sizeof(double) * n * n);

    m[0] = 3;
    m[1] = -9;
    m[2] = 0;
    m[3] = -9;

    m[4] = -3;
    m[5] = -6;
    m[6] = 26;
    m[7] = 2;

    m[8] = -1;
    m[9] = 2;
    m[10] = 4;
    m[11] = 7;

    m[12] = 1;
    m[13] = -2;
    m[14] = -2;
    m[15] = -3;
    return m;
  }
  throw std::runtime_error("Invalid matrix size passed to genMatrix");
}