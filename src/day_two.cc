#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Solution {
public:
  uint64_t part_one(const std::vector<std::string> &input) const {
    uint64_t sum = 0;
    if (input.empty())
      return sum;

    std::stringstream ranges{input[0]};
    std::string range;
    while (std::getline(ranges, range, ',')) {
      size_t hyphen = range.find('-');
      if (hyphen == std::string::npos)
        continue;
      uint64_t start = std::stoull(range.substr(0, hyphen));
      uint64_t end = std::stoull(range.substr(hyphen + 1));
      for (uint64_t i = start; i <= end; ++i) {
        std::string s = std::to_string(i);
        if (has_equal_halves(s))
          sum += i;
      }
    }

    return sum;
  }

  uint64_t part_two(const std::vector<std::string> &input) const {
    uint64_t sum = 0;
    if (input.empty())
      return sum;

    std::stringstream ranges{input[0]};
    std::string range;
    while (std::getline(ranges, range, ',')) {
      size_t hyphen = range.find('-');
      if (hyphen == std::string::npos)
        continue;
      uint64_t start = std::stoull(range.substr(0, hyphen));
      uint64_t end = std::stoull(range.substr(hyphen + 1));
      for (uint64_t i = start; i <= end; ++i) {
        std::string s = std::to_string(i);
        if (is_repetition(s))
          sum += i;
      }
    }

    return sum;
  }

private:
  static bool has_equal_halves(const std::string &nums) {
    size_t len = nums.size();
    if (len % 2 != 0)
      return false;
    size_t n = len / 2;
    return nums.substr(0, n) == nums.substr(n, n);
  }

  static bool is_repetition(const std::string &num) {
    size_t len = num.size();
    if (len < 2)
      return false;
    for (size_t sub_len = 1; sub_len <= len / 2; ++sub_len) {
      if (len % sub_len != 0)
        continue;
      std::string piece = num.substr(0, sub_len);
      bool ok = true;
      for (size_t pos = sub_len; pos < len; pos += sub_len) {
        if (num.substr(pos, sub_len) != piece) {
          ok = false;
          break;
        }
      }
      if (ok)
        return true;
    }
    return false;
  }
};

template <typename T> std::vector<T> reader(const std::string &path) {
  std::ifstream file(path);
  std::vector<T> content;
  if (!file.is_open())
    return content;
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
  std::vector<std::string> input = reader<std::string>("inputs/day_two.txt");
  Solution solution;
  std::cout << solution.part_one(input) << std::endl;
  std::cout << solution.part_two(input) << std::endl;
  return 0;
}
