#include "DenseMatrixParser.hh"

#include <io.h>

#include <experimental/filesystem> // Header file for pre-standard implementation
#include <filesystem>              // C++17 standard header file name
namespace fs = std::experimental::filesystem::v1;
// namespace fs = filesystem;
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::stod;
DenseMatrixParser::DenseMatrixParser() {}

DenseMatrix *DenseMatrixParser::fromMTX(string filepath) {
  // Make sure the path exists, using an absolute filepath for clarity
  fs::path path(filepath);
  this->filepath = fs::absolute(path).string();
  if (_access(this->filepath.c_str(), 04) != 0) {
    throw std::runtime_error(
        "Attempted to read " + this->filepath +
        " but the file does not exist or is not readable.");
  }

  // Read in the file, skipping comments
  ifstream input_file(this->filepath);
  string ln;
  bool printed_header_line = false;
  bool read_dims = false;
  int n_entries;
  while (getline(input_file, ln)) {
    if (ln.length() <= 1) {
      continue; // probably an empty newline
    } else if (ln.at(0) == comment_char) {
      if (!printed_header_line) {
        // cout << "Header:\n" << ln.substr(2, ln.length()) << endl;
        printed_header_line = true;
      }
      continue; // Either a comment or a header line
    } else {
      if (!read_dims) {
        const int max_index = ln.length();
        int index = 0;
        int last_index = 0;
        // Identify the first space
        while (ln.at(index) != ' ')
          index++;
        const int n_rows = atoi(ln.substr(last_index, index++).c_str());
        last_index = index;
        // identify the second space
        while (ln.at(index) != ' ')
          index++;
        const int n_cols = atoi(ln.substr(last_index, index++).c_str());
        // get the number of entries
        n_entries = atoi(ln.substr(index, max_index).c_str());
        // cout << "Got NROWS: " << n_rows << "\t NCOLS: " << n_cols
        //      << "\t ENTRIES: " << n_entries << endl;
        dm = new DenseMatrix(n_rows, n_cols);
        read_dims = true;
      } else {
        const int max_index = ln.length();
        int index = 0;
        int last_index = 0;
        // Identify the first space
        while (ln.at(index) != ' ')
          index++;
        const int row = atoi(ln.substr(last_index, index++).c_str());
        last_index = index;
        // identify the second space
        while (ln.at(index) != ' ')
          index++;
        const int col = atoi(ln.substr(last_index, index++).c_str());
        // get the double
        double val = stod(ln.substr(index, max_index));
        dm->set_at(row, col, val);
      }
    }
  }
  return dm;
}
