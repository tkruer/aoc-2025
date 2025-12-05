#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
  bool isFresh(const std::vector<std::pair<long long, long long>> &ranges,
               const std::string &s) const {
    long long num = std::stoll(s);
    for (const auto &r : ranges)
      if (num >= r.first && num <= r.second)
        return true;
    return false;
  }

  long long isFreshCount(
      const std::vector<std::pair<long long, long long>> &ranges) const {
    if (ranges.empty())
      return 0;
    std::vector<std::pair<long long, long long>> r = ranges;
    std::sort(r.begin(), r.end());
    long long currentStart = r[0].first;
    long long currentEnd = r[0].second;
    long long freshCount = 0;
    for (size_t i = 1; i < r.size(); ++i) {
      auto [s, e] = r[i];
      if (s <= currentEnd) {
        currentEnd = std::max(currentEnd, e);
      } else {
        freshCount += (currentEnd - currentStart) + 1;
        currentStart = s;
        currentEnd = e;
      }
    }
    freshCount += (currentEnd - currentStart) + 1;
    return freshCount;
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
  auto lines = reader<std::string>("inputs/day_five.txt");
  Solution sol;
  std::vector<std::pair<long long, long long>> ranges;
  bool readingRanges = true;
  long long freshCountPartTwo = 0;
  int freshCount = 0;

  for (const auto &line : lines) {
    if (line.empty()) {
      readingRanges = false;
      continue;
    }
    if (readingRanges) {
      std::size_t dashPos = line.find('-');
      if (dashPos == std::string::npos)
        continue;
      long long startRange = std::stoll(line.substr(0, dashPos));
      long long endRange = std::stoll(line.substr(dashPos + 1));
      ranges.emplace_back(startRange, endRange);
    } else {
      if (sol.isFresh(ranges, line))
        ++freshCount;
    }
  }

  freshCountPartTwo = sol.isFreshCount(ranges);
  std::cout << "Part 1: " << freshCount << std::endl;
  std::cout << "Part 2: " << freshCountPartTwo << std::endl;
  return 0;
}
