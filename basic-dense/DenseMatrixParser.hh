#ifndef DenseMatrixParserHH

#include <string>

#include "DenseMatrix.hh"

using std::string;

class DenseMatrixParser {
 private:
  string filepath = "";
  DenseMatrix* dm = nullptr;

 public:
  DenseMatrixParser();
  DenseMatrix* fromMTX(string filepath);
  const char comment_char = '%';
};

#define DenseMatrixParserHH
#endif
