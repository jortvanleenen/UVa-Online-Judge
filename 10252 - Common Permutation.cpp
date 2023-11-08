/**
 * This file contains my solution to the UVa 10252 - "Common Permutation" 
 * problem.
 * https://onlinejudge.org/external/102/10252.pdf
 *
 * @file
 * @author Jort van Leenen
 * @copyright GNU General Public License v3.0
 */

#include <iostream>
#include <array>

std::array<int, 26> getLetterFrequency(const std::string& word) {
  std::array<int, 26> letters{};
  for (auto letter: word) {
    ++letters[letter - 'a'];
  }

  return letters;
}

std::string commonPermutation(const std::string& first_word,
                              const std::string& second_word) {
  std::array<int, 26> first_word_letters{getLetterFrequency(first_word)};
  std::array<int, 26> second_word_letters{getLetterFrequency(second_word)};

  std::string common_permutation{""};
  for (int i{0}; i < 26; ++i) {
    int min{std::min(first_word_letters[i], second_word_letters[i])};
    for (int j{0}; j < min; ++j) {
      common_permutation += static_cast<char>(i + 'a');
    }
  }

  return common_permutation;
}

int main() {
  std::string line{};
  while (getline(std::cin, line)) {
    std::string first_word{line};
    getline(std::cin, line);
    std::string second_word{line};

    std::cout << commonPermutation(first_word, second_word) << '\n';
  }

  return 0;
}
