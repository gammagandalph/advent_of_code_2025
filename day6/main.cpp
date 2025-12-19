#include "util.h"
#include <cstdio>
#include <vector>

long solve(std::vector<day6::Problem> input) {
  long total = 0;
  for (auto problem : input) {
    // std::cout << problem.toString() << std::endl;
    long subtotal;
    if (problem.op == '*') {
      subtotal = 1;
      for (auto n : problem.inputs) {
        subtotal *= n;
      }
    }
    if (problem.op == '+') {
      subtotal = 0;
      for (auto n : problem.inputs) {
        subtotal += n;
      }
    }
    total += subtotal;
  }
  return total;
}

int main(int argc, char *argv[]) {
  auto inputPart1 = day6::readFilePart1(argv[1]);
  printf("Total Part 1: %ld\n", solve(inputPart1));

  auto inputPart2 = day6::readFilePart2(argv[1]);
  printf("Total Part 2: %ld\n", solve(inputPart2));

  return 0;
}
