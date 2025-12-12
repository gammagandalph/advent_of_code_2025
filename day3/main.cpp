#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> LoadFile(std::string file) {
  std::ifstream InputFile(file);
  std::vector<std::string> result;
  std::string buf;
  while (getline(InputFile, buf)) {
    result.push_back(buf);
  }
  return result;
}

int FindIndexOfHighest(std::string input) {
  int curIndex, buf = 0;
  for (int i = 0; i < input.size(); i++) {
    int value = input.at(i) - '0';
    if (value > buf) {
      buf = value;
      curIndex = i;
    }
  }
  return curIndex;
}

void part1(std::string filename) {
  std::vector<std::string> input = LoadFile(filename);
  int total = 0;
  for (std::string line : input) {
    // find the largest digit, unless it's in the last position of the line
    int index1 = FindIndexOfHighest(line.substr(0, line.length() - 1));
    // find the largest digit in the remaining string and translate it into an
    // index into the original line
    int index2 = FindIndexOfHighest(line.substr(index1 + 1)) + index1 + 1;
    std::stringstream builder;
    builder << line.at(index1) << line.at(index2);
    total += std::stoi(builder.str());
  }
  printf("Total safe charge: %d\n", total);
}

void part2(std::string filename) {
  std::vector<std::string> input = LoadFile(filename);
  unsigned long long total = 0;
  for (std::string line : input) {
    std::stringstream builder;
    int index = -1;
    for (int i = 0; i < 12; i++) {
      // set our start at the last found index
      int start = index + 1;
      // make sure there's enough left to fill out a 12 digit number
      int len = line.length() - (11 - i) - start;

      //  find the index of the highest digit in the substring
      std::string sub = line.substr(start, len);
      index = FindIndexOfHighest(sub);

      // translate the index to an index on the original line
      index = start + index;

      // add the digit to our string builder
      builder << line.at(index);
    }
    total += std::stoull(builder.str());
  }
  printf("Total unsafe charge: %llu\n", total);
}

int main(int argc, char *argv[]) {
  part1(argv[1]);
  part2(argv[1]);
  return 0;
}
