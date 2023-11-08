/**
 * This file contains my solution to the UVa 10042 - "Smith Numbers" problem.
 * https://onlinejudge.org/external/100/10042.pdf
 *
 * @file
 * @author Jort van Leenen
 * @copyright GNU General Public License v3.0
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <cmath>

int sumDigits(int number) {
  number = std::abs(number);
  int sum{0};
  while (number > 0) {
    sum += number % 10;
    number /= 10;
  }
  return sum;
}

int sumDigitsVector(const std::vector<int>& vector) {
  int sum{0};
  for (auto number: vector) {
    sum += sumDigits(number);
  }
  return sum;
}

std::vector<int> getPrimeFactors(const std::set<int>& primes, int number) {
  std::vector<int> prime_factors{};
  for (auto prime: primes) {
    while (number % prime == 0) {
      prime_factors.push_back(prime);
      number /= prime;
    }
  }

  if (number > 1) {
    prime_factors.push_back(number);
  }

  return prime_factors;
}

bool isPrime(const std::set<int>& primes, int number) {
  if (number < 2) {
    return false;
  }
  for (auto prime: primes) {
    if (prime > static_cast<int>(std::sqrt(number))) {
      break;
    } else if (number % prime == 0) {
      return false;
    }
  }

  return true;
}

int findLargerSmithNumber(const std::set<int>& primes, int number) {
  while (true) {
    ++number;
    if (!isPrime(primes, number)) {
      const int sum_of_digits{sumDigits(number)};
      std::vector<int> prime_factors{getPrimeFactors(primes, number)};
      const int sum_of_prime_factors{sumDigitsVector(prime_factors)};
      if (sum_of_digits == sum_of_prime_factors) {
        return number;
      }
    }
  }
}

std::set<int> getPrimes(int upper_bound) {
  std::set<int> primes{};
  for (int i{2}; i <= upper_bound; ++i) {
    if (!isPrime(primes, i)) {
      continue;
    }

    bool is_prime{true};
    for (int j{2}; j <= static_cast<int>(std::sqrt(i)); ++j) {
      if (!isPrime(primes, j)) {
        continue;
      }
      if (i % j == 0) {
        is_prime = false;
        break;
      }
    }

    if (is_prime) {
      primes.insert(i);
    }
  }

  return primes;
}

int main() {
  std::set<int> primes{getPrimes(static_cast<int>(std::sqrt(1000000000)))};

  std::string line{};
  std::getline(std::cin, line); // Ignore number of test cases, not needed
  while (std::getline(std::cin, line)) {
    const int number{std::stoi(line)};
    std::cout << findLargerSmithNumber(primes, number) << '\n';
  }

  return EXIT_SUCCESS;
}
