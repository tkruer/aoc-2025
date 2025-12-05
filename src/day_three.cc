#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

class Solution {
public:
  int part_one(const std::string &s) const {
    int maxJoltage = 0;
    int len = static_cast<int>(s.length());
    for (int i = 0; i < len - 1; ++i) {
      int d1 = s[i] - '0';
      for (int j = i + 1; j < len; ++j) {
        int d2 = s[j] - '0';
        int val = 10 * d1 + d2;
        if (val > maxJoltage)
          maxJoltage = val;
      }
    }
    return maxJoltage;
  }

  std::uint64_t part_two(const std::string &s) const {
    int len = static_cast<int>(s.length());
    int remove = len - 12;
    if (remove <= 0) {
      std::uint64_t val = 0;
      for (char c : s)
        val = val * 10 + (c - '0');
      return val;
    }

    std::string result;
    result.reserve(len - remove);
    for (char c : s) {
      while (remove > 0 && !result.empty() && result.back() < c) {
        result.pop_back();
        --remove;
      }
      result.push_back(c);
    }

    if (remove > 0)
      result.erase(result.size() - remove);

    if (static_cast<int>(result.size()) > 12)
      result.resize(12);

    std::uint64_t maxJoltage = 0;
    for (char c : result)
      maxJoltage = maxJoltage * 10 + static_cast<std::uint64_t>(c - '0');
    return maxJoltage;
  }
};

template <typename T> std::vector<T> reader(const std::string &path) {
  std::ifstream file(path);
  std::vector<T> content;
  if (!file.is_open())
    return content;
  std::string line;
  while (std::getline(file, line)) {
    if constexpr (std::is_same_v<T, int>)
      content.push_back(std::stoi(line));
    else if constexpr (std::is_same_v<T, std::string>)
      content.push_back(line);
  }
  return content;
}

int main() {
  std::vector<std::string> input = reader<std::string>("inputs/day_three.txt");
  Solution solution;
  std::uint64_t total_part_one = 0;
  std::uint64_t total_part_two = 0;

  for (const auto &line : input) {
    if (line.empty())
      continue;
    total_part_one += static_cast<std::uint64_t>(solution.part_one(line));
    total_part_two += solution.part_two(line);
  }

  std::cout << "Part One: " << total_part_one << std::endl;
  std::cout << "Part Two: " << total_part_two << std::endl;
  return 0;
}
