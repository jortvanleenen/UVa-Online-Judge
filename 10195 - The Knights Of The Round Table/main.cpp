/**
* This file contains my solution to the UVa 10195 - "The Knights Of The Round
* Table" problem.
*
* Note: to prepare for an upcoming programming contest, I switched to a
* different IDE for the programming of this problem due to that IDE being the
* only one available during the contest. Formatting may be slightly different.
*
* @file
* @author Jort van Leenen
* @copyright GNU General Public License v3.0
*/

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <iomanip>

double fittingRadius (double a, double b, double c) {
  double s = 0.5 * (a + b + c); // semiperimeter
  double area = std::sqrt (s * (s - a) * (s - b) * (s - c)); // Heron's formula
  if (a == 0 || b == 0 || c == 0) {
    area = 0;
    s = 1;
  }
  return area / s;
}

int main() {
  std::string line{};
  while (std::getline (std::cin, line) ) {
    std::istringstream stream{line};
    double a{};
    double b{};
    double c{};
    stream >> a >> b >> c;

    std::cout << "The radius of the round table is: "
              << std::fixed << std::setprecision(3)
              << fittingRadius (a, b, c) << '\n';
  }
  return 0;
}
