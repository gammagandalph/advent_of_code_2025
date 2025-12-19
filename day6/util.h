#include <cctype>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace day6 {

struct Problem {
  std::vector<long> inputs;
  char op;
  std::string toString() {
    std::stringstream ss;
    ss << op << " (";
    for (int i = 0; i < inputs.size(); ++i) {
      ss << inputs.at(i);
      if (i != inputs.size() - 1)
        ss << ", ";
    }
    ss << ')';
    return ss.str();
  }
};

inline std::vector<Problem> readFilePart1(std::string filename) {
  std::vector<Problem> problems = {};
  std::ifstream file(filename);

  std::string lineBuf;
  getline(file, lineBuf);

  // handle first line to initialise the Problems
  int pos = 0;
  while (pos < lineBuf.length()) {
    pos = lineBuf.find_first_not_of(' ', pos);

    if (pos < 0)
      break;

    Problem p;
    size_t length = lineBuf.find_first_of(' ', pos) - pos;
    long number = std::stol(lineBuf.substr(pos, length));
    p.inputs = {number};

    problems.push_back(p);

    pos += length;
  }

  // handle the rest of the lines
  while (getline(file, lineBuf)) {
    int pIndex = 0;
    int pos = 0;

    while (pos < lineBuf.length()) {
      pos = lineBuf.find_first_not_of(' ', pos);

      if (pos < 0)
        break;

      if (lineBuf.at(pos) == '\n') {
        pIndex = 0;
      }
      if (lineBuf.at(pos) >= '0' && lineBuf.at(pos) <= '9') {

        size_t length = lineBuf.find_first_of(' ', pos) - pos;
        long number = std::stol(lineBuf.substr(pos, length));

        problems.at(pIndex).inputs.push_back(number);
        pos += length;
      } else {
        problems.at(pIndex).op = lineBuf.at(pos);
        ++pos;
      }
      ++pIndex;
    }
  }

  return problems;
}

struct MathProblemMatrix {
  std::string matrix;
  size_t cols;
  size_t rows;
  MathProblemMatrix(std::string input) {
    size_t len = input.find('\n');
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());

    matrix = input + ' ';

    rows = matrix.length() / len;
    cols = len;
  }
  char charAt(size_t row, size_t col) { return matrix.at(row * cols + col); }
  bool charIsDigit(size_t row, size_t col) {
    return std::isdigit(charAt(row, col));
  }
};

inline std::vector<Problem> readFilePart2(std::string filename) {
  std::vector<Problem> problems = {};
  std::ifstream file(filename);
  std::stringstream buf;
  buf << file.rdbuf();
  MathProblemMatrix m(buf.str());

  std::string numBuf = "";
  std::vector<long> inputsBuf = {};
  for (int col = m.cols - 1; col >= 0; --col) {
    for (int row = 0; row < m.rows; ++row) {
      if (std::isspace(m.charAt(row, col))) {
        if (numBuf != "") {
          inputsBuf.push_back(std::stol(numBuf));
          numBuf = "";
        }
      }
      if (m.charIsDigit(row, col)) {
        numBuf.push_back(m.charAt(row, col));
      }
      if (m.charAt(row, col) == '+' || m.charAt(row, col) == '*') {
        if (numBuf != "")
          inputsBuf.push_back(std::stol(numBuf));
        problems.push_back({inputsBuf, m.charAt(row, col)});
        numBuf = "";
        inputsBuf.clear();
      }
    }
  }

  return problems;
}

} // namespace day6
