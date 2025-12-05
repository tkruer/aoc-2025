#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Solution {
public:
  int part_one(const std::vector<std::string> &grid, int rows, int cols) const {
    int good = 0;
    static const std::vector<std::pair<int, int>> off = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (grid[i][j] != '@')
          continue;
        int neighbors = 0;
        for (auto [di, dj] : off) {
          int ni = i + di;
          int nj = j + dj;
          if (ni < 0 || nj < 0 || ni >= rows || nj >= cols)
            continue;
          if (grid[ni][nj] == '@')
            ++neighbors;
        }
        if (neighbors < 4)
          ++good;
      }
    }
    return good;
  }

  long long part_two(std::vector<std::string> grid, int rows, int cols) const {
    long long removed = 0;
    static const std::vector<std::pair<int, int>> off = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    while (true) {
      std::vector<std::pair<int, int>> toRemove;
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          if (grid[i][j] != '@')
            continue;
          int neighbors = 0;
          for (auto [di, dj] : off) {
            int ni = i + di;
            int nj = j + dj;
            if (ni < 0 || nj < 0 || ni >= rows || nj >= cols)
              continue;
            if (grid[ni][nj] == '@')
              ++neighbors;
          }
          if (neighbors < 4)
            toRemove.emplace_back(i, j);
        }
      }
      if (toRemove.empty())
        break;
      for (auto [r, c] : toRemove) {
        grid[r][c] = '.';
        ++removed;
      }
    }
    return removed;
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
  auto lines = reader<std::string>("inputs/day_four.txt");
  std::vector<std::vector<std::string>> grids;
  std::vector<std::string> cur;
  for (auto &ln : lines) {
    if (ln.empty()) {
      if (!cur.empty()) {
        grids.push_back(cur);
        cur.clear();
      }
    } else {
      cur.push_back(ln);
    }
  }
  if (!cur.empty())
    grids.push_back(cur);

  Solution sol;
  for (size_t k = 0; k < grids.size(); ++k) {
    const auto &g = grids[k];
    if (g.empty())
      continue;
    int rows = static_cast<int>(g.size());
    int cols = static_cast<int>(g[0].size());
    int p1 = sol.part_one(g, rows, cols);
    long long p2 = sol.part_two(g, rows, cols);
    std::cout << "Grid " << k + 1 << " Part 1: " << p1 << std::endl;
    std::cout << "Grid " << k + 1 << " Part 2: " << p2 << std::endl;
  }

  return 0;
}
