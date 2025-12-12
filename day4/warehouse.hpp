#include <functional>
#import <vector>

struct Position {
  std::size_t row;
  std::size_t col;
  Position(size_t row, size_t col);
  std::string toString();
};

class Warehouse {

private:
  std::vector<std::vector<char>> m_matrix;
  char m_empty;
  char m_item;
  std::size_t m_rows;
  std::size_t m_cols;
  int m_maxAdj;

public:
  Warehouse(std::string input);
  std::vector<std::vector<char>> matrix();
  void forEach(std::function<void(Position)> func);
  void remove(Position pos);
  char at(Position pos);
  bool isOutOfBounds(Position pos);
  bool itemAt(Position pos);
  bool emptyAt(Position pos);
  bool forkliftReachable(Position pos);
  std::string toString();
};

class OutOfBoundsException : public std::exception {
public:
  std::string what() { return "Position is out of bounds"; }
};
