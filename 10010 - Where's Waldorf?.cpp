/**
 * This file contains my solution to the UVa 10010 - "Where's Waldorf?" problem.
 * https://onlinejudge.org/external/100/10010.pdf
 *
 * @file
 * @author Jort van Leenen
 * @copyright GNU General Public License v3.0
 */

#include <iostream>
#include <array>
#include <vector>

void readGrid(std::vector<std::vector<char>>& grid) {
  for (int row{0}; row < grid.size(); ++row) {
    std::string line{};
    getline(std::cin, line);
    for (int column{0}; column < grid[row].size(); ++column) {
      grid[row][column] = static_cast<char>(std::tolower(line[column]));
    }
  }
}

std::string getNextWord() {
  std::string word{};
  getline(std::cin, word);
  for (auto& character: word) {
    character = static_cast<char>(std::tolower(character));
  }

  if (word[word.size() - 1] == '\r') {
    word = word.substr(0, word.size() - 1);
  }

  return word;
}

bool isOccurrence(const std::string& word,
                  const std::vector<std::vector<char>>& grid,
                  int row,
                  int column) {
  std::array<std::array<int, 2>, 8> directions{
      std::array<int, 2>{-1, -1}, std::array<int, 2>{-1, 0},
      std::array<int, 2>{-1, 1}, std::array<int, 2>{0, -1},
      std::array<int, 2>{0, 1}, std::array<int, 2>{1, -1},
      std::array<int, 2>{1, 0}, std::array<int, 2>{1, 1}};

  for (const auto& direction: directions) {
    if (direction[0] * (word.size() - 1) + row >= grid.size() ||
        direction[0] * (word.size() - 1) + row < 0 ||
        direction[1] * (word.size() - 1) + column >= grid[row].size() ||
        direction[1] * (word.size() - 1) + column < 0) {
      continue;
    }

    for (int i{0}; i < word.size(); ++i) {
      if (grid[row + i * direction[0]][column + i * direction[1]] != word[i]) {
        break;
      }
      if (i == word.size() - 1) {
        return true;
      }
    }
  }
  return false;
}

std::pair<int, int> findWord(const std::string& word,
                             const std::vector<std::vector<char>>& grid) {
  for (int row{0}; row < grid.size(); ++row) {
    for (int column{0}; column < grid[row].size(); ++column) {
      if (isOccurrence(word, grid, row, column)) {
        return std::pair<int, int>{row, column};
      }
    }
  }
  return std::pair<int, int>{-1, -1}; // Should not be reachable if valid input
}

int main() {
  std::string line{};
  getline(std::cin, line);
  int test_cases{std::stoi(line)};

  for (int i{0}; i < test_cases; ++i) {
    getline(std::cin, line); // Remove empty line

    getline(std::cin, line); // Get grid size, format: "<rows> <columns>"
    const std::pair<int, int> size{std::stoi(line.substr(0, line.find(' '))),
                                   std::stoi(line.substr(line.find(' ') + 1))};
    std::vector<std::vector<char>> grid(size.first,
                                        std::vector<char>(size.second));

    readGrid(grid);

    getline(std::cin, line); // Get number of words, format: "<number_of_words>"
    const int number_of_words{std::stoi(line)};
    for (int j{0}; j < number_of_words; ++j) {
      std::string word{getNextWord()};
      std::pair<int, int> position{findWord(word, grid)};
      std::cout << position.first + 1 << " " << position.second + 1 << '\n';
    }
    if (i < test_cases - 1) {
      std::cout << '\n';
    }
  }
}
