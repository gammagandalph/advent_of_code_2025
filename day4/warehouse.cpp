#include "warehouse.hpp"
#include <cstddef>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Position::Position(size_t _row, size_t _col) {
  row = _row;
  col = _col;
}

std::string Position::toString() {
  std::stringstream s;
  s << '(' << row << ", " << col << ')';
  return s.str();
}

Warehouse::Warehouse(std::string input) {
  m_empty = '.';
  m_item = '@';
  m_maxAdj = 3;

  std::stringstream s(input);
  std::string line;
  while (std::getline(s, line)) {
    std::vector<char> buf;
    for (char c : line) {
      buf.push_back(c);
    }
    m_matrix.push_back(buf);
    buf.clear();
  }

  m_rows = m_matrix.size();
  m_cols = m_matrix.at(0).size();
}

std::vector<std::vector<char>> Warehouse::matrix() { return m_matrix; }

void Warehouse::forEach(std::function<void(Position)> func) {
  for (size_t row = 0; row < this->matrix().size(); row++) {
    for (size_t col = 0; col < this->matrix().at(row).size(); col++) {
      Position p(row, col);
      func(p);
    }
  }
}

bool Warehouse::isOutOfBounds(Position pos) {
  return pos.row >= m_rows || pos.col >= m_cols;
}

char Warehouse::at(Position pos) {
  if (isOutOfBounds(pos))
    throw OutOfBoundsException();
  return m_matrix.at(pos.row).at(pos.col);
}

bool Warehouse::itemAt(Position pos) {
  if (isOutOfBounds(pos))
    throw OutOfBoundsException();
  return this->at(pos) == m_item;
}

bool Warehouse::emptyAt(Position pos) {
  if (isOutOfBounds(pos))
    throw OutOfBoundsException();
  return this->at(pos) == m_empty;
}

bool Warehouse::forkliftReachable(Position pos) {
  if (isOutOfBounds(pos))
    throw OutOfBoundsException();

  if (!itemAt(pos))
    return false;

  int currAdj = 0;

  Position positions[8] = {
      {pos.row - 1, pos.col - 1}, {pos.row - 1, pos.col},
      {pos.row - 1, pos.col + 1},

      {pos.row, pos.col - 1},     {pos.row, pos.col + 1},

      {pos.row + 1, pos.col - 1}, {pos.row + 1, pos.col},
      {pos.row + 1, pos.col + 1},
  };

  for (Position position : positions) {
    try {
      currAdj += itemAt(position) ? 1 : 0;
      if (currAdj > m_maxAdj)
        return false;
    } catch (OutOfBoundsException e) {
    }
  }

  return currAdj <= m_maxAdj;
}

void Warehouse::remove(Position pos) {
  if (isOutOfBounds(pos))
    throw OutOfBoundsException();
  m_matrix.at(pos.row).at(pos.col) = m_empty;
}

std::string Warehouse::toString() {
  std::stringstream buf;
  for (std::vector<char> row : m_matrix) {
    for (char c : row) {
      buf << c;
    }
    buf << std::endl;
  }
  return buf.str();
}
