#include "warehouse_v2.hpp"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <string>

Warehouse::Warehouse(std::string input) {
  m_empty = '.';
  m_item = '@';
  m_maxAdj = 3;

  int len = input.find('\n');
  input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());

  m_matrix = input;

  m_rows = m_matrix.length() / len;
  m_cols = len;
}

std::string Warehouse::matrix() { return m_matrix; }

void Warehouse::forEach(std::function<void(size_t)> func) {
  for (size_t row = 0; row < m_rows; row++) {
    for (size_t col = 0; col < m_cols; col++) {
      size_t pos = row * m_cols + col;
      func(pos);
    }
  }
}

bool Warehouse::rEdge(size_t pos) { return pos % m_cols == m_cols - 1; }
bool Warehouse::lEdge(size_t pos) { return pos == 0 || pos % m_cols == 0; }
bool Warehouse::tEdge(size_t pos) { return pos < m_cols; }
bool Warehouse::bEdge(size_t pos) { return pos >= m_matrix.length() - m_cols; }

char Warehouse::at(size_t pos) { return m_matrix.at(pos); }

bool Warehouse::itemAt(size_t pos) { return m_matrix.at(pos) == m_item; }

bool Warehouse::emptyAt(size_t pos) { return m_matrix.at(pos) == m_empty; }

bool Warehouse::forkliftReachable(size_t pos) {
  if (!itemAt(pos))
    return false;

  int neighbours = 0;

  neighbours += !rEdge(pos) && m_matrix.at(pos + 1) != m_empty ? 1 : 0;
  neighbours += !lEdge(pos) && m_matrix.at(pos - 1) != m_empty ? 1 : 0;
  neighbours += !tEdge(pos) && m_matrix.at(pos - m_cols) != m_empty ? 1 : 0;
  neighbours += !bEdge(pos) && m_matrix.at(pos + m_cols) != m_empty ? 1 : 0;

  neighbours +=
      !rEdge(pos) && !tEdge(pos) && m_matrix.at(pos + 1 - m_cols) != m_empty
          ? 1
          : 0;
  neighbours +=
      !lEdge(pos) && !tEdge(pos) && m_matrix.at(pos - 1 - m_cols) != m_empty
          ? 1
          : 0;

  neighbours +=
      !rEdge(pos) && !bEdge(pos) && m_matrix.at(pos + 1 + m_cols) != m_empty
          ? 1
          : 0;
  neighbours +=
      !lEdge(pos) && !bEdge(pos) && m_matrix.at(pos - 1 + m_cols) != m_empty
          ? 1
          : 0;

  return neighbours < 4;
}

void Warehouse::remove(size_t pos) { m_matrix.at(pos) = m_empty; }

std::string Warehouse::toString() {
  std::string result = m_matrix;
  for (size_t i = 0; i < m_rows; ++i) {
    result.insert(i * m_cols + m_cols + i, 1, '\n');
  }
  return result;
}
