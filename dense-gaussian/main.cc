#include <iostream>

#include "DenseMatrix.hh"
#include "DenseMatrixParser.hh"
#include "LU_Dense_Gaussian.hh"
using namespace std;

int main() {
  DenseMatrixParser dmp;
  DenseMatrix dm = *(dmp.fromMTX("Mat16_16.mtx"));
  LU_Dense_Gaussian ludg(&dm);
  ludg.solve();
  cout << "Original Matrix:\n" << dm << endl;
  cout << "Upper Matrix:\n" << *(ludg.get_upper()) << endl;
  cout << "Lower Matrix:\n" << *(ludg.get_lower()) << endl;
  delete &dm;
}

// Basic Setting/Getting
// int main() {
//   DenseMatrix dm1 = DenseMatrix(3, 4);
//   dm1.set_at(0, 0, 5);
//   dm1.set_at(0, 3, 10);
//   cout << dm1.get_at(0, 3);
// }

// Copy Constructor Verified
// int main() {
//   DenseMatrix dm1 = DenseMatrix(3, 4);
//   DenseMatrix dm2(dm1);
// }

// Basic Constructor Verified
// int main() {
//   DenseMatrix dm1 = DenseMatrix(3, 4);
//   cout << "DONE" << endl;
// }
