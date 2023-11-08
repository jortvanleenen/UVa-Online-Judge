/**
 * This file contains my solution to the UVa 10157 - "Expressions" problem.
 * https://onlinejudge.org/external/101/10157.pdf
 *
 * It is NOT ACCEPTED by Online Judge due to it not implementing a BigInt class
 * or similar structure. It can still be used to upload a working solution by
 * implementing below code in e.g. Python.
 *
 * @file
 * @author Jort van Leenen
 * @copyright GNU General Public License v3.0
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

__uint128_t countExpressions(int parentheses, int depth_d,
                             std::vector<std::vector<__uint128_t>>& memo,
                             std::vector<std::vector<bool>>& memo_set) {
  if (parentheses % 2 == 1) {
    return 0;
  }

  const int pairs{parentheses / 2};
  if (memo_set[pairs][depth_d]) {
    return memo[pairs][depth_d];
  } else if (pairs < depth_d) {
    memo[pairs][depth_d] = 0;
    memo_set[pairs][depth_d] = true;
    return 0;
  } else if (pairs == depth_d || pairs == 1 || depth_d == 1) {
    memo[pairs][depth_d] = 1;
    memo_set[pairs][depth_d] = true;
    return 1;
  } else if (pairs == 0 || depth_d == 0) {
    memo[pairs][depth_d] = 0;
    memo_set[pairs][depth_d] = true;
    return 0;
  }


  __uint128_t count{0};

  for (int i{0}; i < parentheses; i += 2) {
    __uint128_t first{0};
    for (int j{1}; j < depth_d; ++j) {
      first += countExpressions(i, j, memo, memo_set);
    }
    first = first == 0 ? 1 : first;
    first *= countExpressions(parentheses - i - 2, depth_d, memo, memo_set);

    __uint128_t second{0};
    for (int j{1}; j < depth_d; ++j) {
      second += countExpressions(parentheses - i - 2, j, memo, memo_set);
    }
    second = second == 0 ? 1 : second;
    second *= countExpressions(i, depth_d - 1, memo, memo_set);

    count += first + second;
  }

  memo[pairs][depth_d] = count;
  memo_set[pairs][depth_d] = true;

  return count;
}

std::string toString_uint128_t(__uint128_t number) {
  if (number == 0) {
    return "0";
  }

  std::string result{};
  while (number > 0) {
    result += static_cast<char>(number % 10 + '0');
    number /= 10;
  }
  std::reverse(result.begin(), result.end());

  return result;
}

int main() {
  std::vector<std::vector<__uint128_t>> memo(151,
                                             std::vector<__uint128_t>(151, 0));
  std::vector<std::vector<bool>> memo_set(151, std::vector<bool>(151, false));

  std::string line{};
  while (std::getline(std::cin, line)) {
    if (line.empty() || line[0] == '\r' || line[0] == '\n') {
      continue;
    }

    const int parentheses{std::stoi(line.substr(0, line.find(' ')))};
    const int depth_d{std::stoi(line.substr(line.find(' ') + 1))};

    __uint128_t parenthesis_count{countExpressions(parentheses, depth_d, memo,
                                                   memo_set)};

    std::cout << toString_uint128_t(parenthesis_count) << '\n';
  }

  return EXIT_SUCCESS;
}
