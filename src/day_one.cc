#include <fstream>
#include <iostream>

class Solution {
public:
  int part_one(const std::vector<std::string> &input, int starting_value) {
    std::vector<char> dirs;
    std::vector<int> vals;

    for (const std::string &line : input) {
      if (line.empty())
        continue;

      char dir = std::tolower(line[0]);
      int num = std::stoi(line.substr(1));

      dirs.push_back(dir);
      vals.push_back(num);
    }

    int dial = starting_value;
    int password = 0;
    const int MAX = 100;

    for (size_t i = 0; i < dirs.size(); i++) {
      if (dirs[i] == 'l') {
        dial = (dial - vals[i]) % MAX;
        if (dial < 0)
          dial += MAX;
      } else if (dirs[i] == 'r') {
        dial = (dial + vals[i]) % MAX;
      }

      if (dial == 0) {
        password++;
      }
    }

    return password;
  }

  int part_two(const std::vector<std::string> &input, int starting_value) {
    int dial = starting_value;
    int password = 0;
    const int MAX = 100;

    for (const auto &line : input) {
      char dir = std::toupper(line[0]);
      int rotation = std::stoi(line.substr(1));
      if (dir == 'L')
        rotation = -rotation;

      int boundToAdd = (dial == 0) ? 0 : 1;
      int newPos = dial + (rotation % MAX);

      if (newPos >= MAX) {
        newPos -= MAX;
        password += boundToAdd;
      } else if (newPos < 0) {
        newPos += MAX;
        password += boundToAdd;
      } else if (newPos == 0) {
        password += boundToAdd;
      }

      password += std::abs(rotation / MAX);

      dial = newPos;
    }

    return password;
  }
};

template <typename T> std::vector<T> reader(const std::string &path) {
  std::ifstream file(path);
  std::vector<T> content;

  if (!file.is_open()) {
    return content;
  }
  std::string line;
  while (std::getline(file, line)) {
    if constexpr (std::is_same_v<T, int>) {
      content.push_back(std::stoi(line));
    } else if constexpr (std::is_same_v<T, std::string>) {
      content.push_back(line);
    }
  }

  return content;
}

int main() {
  // read from stdin
  std::vector<std::string> input = reader<std::string>("inputs/day_one.txt");
  Solution solution;
  const int starting_value = 50;
  std::cout << solution.part_one(input, starting_value) << std::endl;
  std::cout << solution.part_two(input, starting_value) << std::endl;
  return 0;
}
