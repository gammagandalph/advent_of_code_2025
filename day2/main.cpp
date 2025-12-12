#include <fstream>
#include <iostream>
#include <string>

#include "../utils.h"

using namespace std;

void day2(string file) {
  ifstream InputFile(file);
  vector<vector<unsigned long long>> tuples;
  while (InputFile.good()) {
    string dataString;
    getline(InputFile, dataString, ',');
    vector<string> v = utils::SplitStringAtChar(dataString, '-');
    tuples.push_back({stoull(v.at(0)), stoull(v.at(1))});
  };
  unsigned long long result, bresult = 0;
  for (vector<unsigned long long> tuple : tuples) {
    unsigned long long position, end;
    end = tuple[1];
    for (position = tuple[0]; position <= end; position++) {
      if (utils::IsDouble(to_string(position)))
        result += position;
      if (utils::IsMultiple(to_string(position))) {
        cout << position << endl;
        bresult += position;
      }
    }
  }
  cout << "Simply doubled: " << result << endl;
  cout << "At least doubled: " << bresult << endl;
}

int main(int argc, char *argv[]) {
  day2(argv[1]);
  return 0;
}
