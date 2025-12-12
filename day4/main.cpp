#include "warehouse.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream file(argv[1]);
  stringstream buf;
  buf << file.rdbuf();
  Warehouse w(buf.str());
  bool someRemoved = true;
  int totalRemoved = 0;
  do {
    int count = 0;
    w.forEach([&w, &count](Position pos) {
      if (w.forkliftReachable(pos)) {
        count++;
        w.remove(pos);
      }
    });
    someRemoved = count > 0;
    totalRemoved += count;
    count = 0;
  } while (someRemoved);
  cout << totalRemoved << endl;
  return 0;
}
