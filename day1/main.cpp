#include <fstream>
#include <string>
#include <vector>
using namespace std;

enum Direction { RIGHT, LEFT };

int doRotation(Direction d, int n, int curPos) {
  int result;
  result = d == LEFT ? curPos - n : curPos + n;
  while (result > 99)
    result = result - 100;
  while (result < 0)
    result = 100 + result;
  return result;
};

int doRotation(Direction dir, int distance, int startingPosition, int &res) {
  res += distance / 100;
  distance = distance % 100;

  int position = startingPosition;

  if (dir == LEFT) {
    position -= distance;
    if (position == 0 && distance != 0) {
      res++;
    } else if (position < 0) {
      if (position + distance != 0)
        res++;
      position += 100;
    }
  }

  if (dir == RIGHT) {
    position += distance;
    if (position > 99) {
      position -= 100;
      res++;
    }
  }

  return position;
};

int rotate(string input, int curPos) {
  Direction d = input[0] == 'L' ? LEFT : RIGHT;
  int n = stoi(input.substr(1));
  return doRotation(d, n, curPos);
};

int rotate(string input, int curPos, int &out) {
  Direction d = input[0] == 'L' ? LEFT : RIGHT;
  int n = stoi(input.substr(1));
  return doRotation(d, n, curPos, out);
};

void day1(string filename) {
  vector<string> rotations;
  string cur;
  ifstream InputFile(filename);

  while (getline(InputFile, cur)) {
    rotations.push_back(cur);
  }

  int res = 0;
  int position = 50;

  for (string rotationString : rotations) {
    position = rotate(rotationString, position);
    if (position == 0)
      ++res;
  }

  printf("The dial pointed at 0 %d times.\n", res);

  res = 0;
  position = 50;

  for (string rotationString : rotations) {
    position = rotate(rotationString, position, res);
  }

  printf("The dial went through 0 %d times.\n", res);
}

int main(int argc, char *argv[]) {
  day1(argv[1]);

  return 0;
}
