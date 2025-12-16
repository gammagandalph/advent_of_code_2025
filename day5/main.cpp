#include "range.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Input {
  std::vector<day5_range::Range<long>> ranges;
  std::vector<long> ids;
};

Input readFile(std::string filename) {
  std::ifstream file(filename);
  std::vector<day5_range::Range<long>> ranges = {};
  std::vector<long> ids = {};
  while (file.good()) {
    std::string buf;
    getline(file, buf);
    if (buf.contains('-')) {
      size_t pos = buf.find('-');
      long start = std::stol(buf.substr(0, pos));
      long end = std::stol(buf.substr(pos + 1));
      day5_range::Range rng(start, end);
      ranges.push_back(rng);
    } else if (buf.empty())
      continue;
    else
      ids.push_back(std::stol(buf));
  }
  return {ranges = ranges, ids = ids};
}

bool isFresh(long id, std::vector<day5_range::Range<long>> ranges) {
  for (auto range : ranges) {
    if (range.contains(id))
      return true;
  }
  return false;
}

std::vector<day5_range::Range<long>>
getFreshRanges(std::vector<day5_range::Range<long>> &ranges) {
  std::sort(ranges.begin(), ranges.end());
  std::vector<day5_range::Range<long>> result = {};
  day5_range::Range<long> buf = ranges.at(0);
  for (auto range = ranges.begin(); range < ranges.end(); ++range) {
    if (buf.overlap(*(range + 1))) {
      buf = buf.combineWith(*(range + 1));
    } else {
      result.push_back(buf);
      buf = *(range + 1);
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  auto [ranges, ids] = readFile(argv[1]);

  // Part 1
  long counter = 0;
  for (auto id : ids) {
    if (isFresh(id, ranges))
      ++counter;
  }

  // Part 2
  unsigned long long total = 0;
  auto freshRanges = getFreshRanges(ranges);

  for (auto range : freshRanges) {
    total += range.length();
  }

  std::cout << "Fresh Items: " << counter << std::endl;
  std::cout << "Total Fresh IDs: " << total << std::endl;

  return 0;
}
