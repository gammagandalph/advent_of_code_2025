#include <cmath>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

namespace utils {
inline vector<string> SplitStringAtChar(string input, char delim) {
  stringstream ss(input);
  vector<string> output;
  string buf;
  while (getline(ss, buf, delim)) {
    output.push_back(buf);
  }
  return output;
}

inline vector<int> GetDivisors(int n) {
  vector<int> divisors;
  for (int i = 1; i <= sqrt(n); i++) {
    if (n % i == 0) {
      int first = i;
      int second = n / i;
      divisors.push_back(first);
      if (first != second && second != n)
        divisors.push_back(n / i);
    }
  }
  return divisors;
}

inline bool IsDouble(string input) {
  // if the string length isn't even, it can't be mirrored
  if (input.length() % 2 != 0)
    return false;

  int halfLength = input.length() / 2;
  string a = input.substr(0, halfLength);
  string b = input.substr(halfLength);
  return a == b;
}

inline bool AreAllSame(vector<string> input) {
  for (int i = 1; i < input.size(); i++) {
    if (input.at(i - 1) != input.at(i)) {
      return false;
    }
  }
  return true;
}

inline vector<string> DivideEqually(string input, int size) {
  vector<string> result;
  int parts = input.length() / size;
  for (int i = 0; i < parts; i++) {
    result.push_back(input.substr(i * size, size));
  }
  return result;
}

inline bool IsMultiple(string input) {
  if (input.length() == 1)
    return false;
  vector<int> divisors = GetDivisors(input.length());
  for (int div : divisors) {
    if (AreAllSame(DivideEqually(input, div)))
      return true;
  }
  return false;
}

} // namespace utils
