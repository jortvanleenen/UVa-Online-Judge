/**
* This file contains my solution to the UVa 10012 - "How Big Is It?" problem.
* https://onlinejudge.org/external/100/10012.pdf
*
* @file
* @author Jort van Leenen
* @copyright GNU General Public License v3.0
*/

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cfloat>

double smallestSuitcase(std::vector<double>& circles) {
  std::vector<double> width_till(circles.size(), 0.0);
  double smallest{DBL_MAX};
  std::sort(circles.begin(), circles.end());
  do {
    double minimum_fitting_width{0.0};
    for (std::size_t i{0}; i < circles.size(); ++i) {
      double current_size{circles[i]};

      for (int j{static_cast<int>(i) - 1}; j >= 0; --j) {
        double hypotenuse = circles[i] + circles[j];
        double vertical_difference = std::abs(circles[i] - circles[j]);
        double horizontal_difference = std::sqrt(
            std::pow(hypotenuse, 2) - std::pow(vertical_difference, 2));

        double horizontal_distance{width_till[j] + horizontal_difference};
        if (horizontal_distance > current_size) {
          current_size = horizontal_distance;
        }
        if (circles[i] <= circles[j]) {
          break;
        }
      }

      width_till[i] = current_size;
      if (width_till[i] + circles[i] > minimum_fitting_width) {
        minimum_fitting_width = width_till[i] + circles[i];
      }
    }

    if (minimum_fitting_width < smallest) {
      smallest = minimum_fitting_width;
    }
  } while (std::next_permutation(circles.begin(), circles.end()));

  return smallest;
}

int main() {
  std::string line{};
  std::getline(std::cin, line); // Ignore line amount specification

  while (std::getline(std::cin, line)) {
    std::istringstream stream{line};
    std::vector<double> circles{};
    double radius{};
    stream >> radius; // Ignore amount of circles
    while (stream >> radius) {
      circles.push_back(radius);
    }

    std::cout << std::fixed << std::setprecision(3)
              << smallestSuitcase(circles) << '\n';
  }
  return 0;
}
