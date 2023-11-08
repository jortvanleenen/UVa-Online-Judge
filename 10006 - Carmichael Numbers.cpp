/**
 * This file contains my solution to the UVa 10006 - "Carmichael Numbers"
 * problem.
 * https://onlinejudge.org/external/100/10006.pdf
 *
 * @file
 * @author Jort van Leenen
 * @copyright GNU General Public License v3.0
 */

#include <iostream>
#include <cmath>

long long power_mod_rec(int base, int exponent, int modulo) {
  if (exponent == 0) {
    return 1;
  }

  if (exponent % 2 == 0) {
    long long result = power_mod_rec(base, exponent / 2, modulo);
    return (result * result) % modulo;
  } else {
    long long result = power_mod_rec(base, exponent - 1, modulo);
    return (result * base) % modulo;
  }
}

long long power_mod(int base, int exponent) {
  return power_mod_rec(base, exponent, exponent);
}

bool isPrime(int number) {
  double upper_limit{std::sqrt(static_cast<double>(number)) + 1};
  for (int i{2}; i <= upper_limit; ++i) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}

bool isCarmichael(int n) {
  if (isPrime(n)) {
    return false;
  }

  for (int a{2}; a < n; ++a) {
    long long result = power_mod(a, n);

    if (result != a) {
      return false;
    }
  }
  return true;
}

int main() {
  int number{};
  while (true) {
    std::cin >> number;
    if (number == 0) {
      break;
    }

    if (isCarmichael(number)) {
      std::cout << "The number " << number << " is a Carmichael number.\n";
    } else {
      std::cout << number << " is normal.\n";
    }
  }
}
