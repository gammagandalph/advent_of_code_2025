#include <functional>
#include <string>

class Warehouse {

private:
  std::string m_matrix;
  char m_empty;
  char m_item;
  std::size_t m_rows;
  std::size_t m_cols;
  int m_maxAdj;
  bool rEdge(size_t pos);
  bool lEdge(size_t pos);
  bool tEdge(size_t pos);
  bool bEdge(size_t pos);

public:
  Warehouse(std::string input);
  std::string matrix();
  void forEach(std::function<void(size_t)> func);
  void remove(size_t pos);
  char at(size_t pos);
  bool isOutOfBounds(size_t pos);
  bool itemAt(size_t pos);
  bool emptyAt(size_t pos);
  bool forkliftReachable(size_t pos);
  std::string toString();
};

class OutOfBoundsException : public std::exception {
public:
  std::string what() { return "size_t is out of bounds"; }
};
