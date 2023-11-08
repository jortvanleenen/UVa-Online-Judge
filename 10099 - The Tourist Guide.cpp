/**
 * This file contains my solution to the UVa 10099 - "The Tourist Guide"
 * problem.
 * https://onlinejudge.org/external/100/10099.pdf
 *
 * @file
 * @author Jort van Leenen
 * @copyright GNU General Public License v3.0
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <climits>
#include <sstream>
#include <cmath>

constexpr int guide{1};

int minimumTrips(std::vector<std::vector<int>>& graph, int start, int end,
                 int tourist_count) {
  std::priority_queue<std::pair<int, std::pair<int, int>>> options;
  std::vector<int> previous(graph.size(), -1);
  previous[start] = start;
  int just_visited{start};
  while (just_visited != end) {
    for (int i{0}; i < graph[just_visited].size(); ++i) {
      if (graph[just_visited][i] == -1 || previous[i] != -1) {
        continue;
      }
      options.emplace(graph[just_visited][i], std::make_pair(just_visited, i));
    }

    while (!options.empty() && previous[options.top().second.second] != -1) {
      options.pop();
    }
    if (options.empty()) {
      break;
    }

    previous[options.top().second.second] = options.top().second.first;
    just_visited = options.top().second.second;
    options.pop();
  }

  if (previous[end] == -1) {
    return 0;
  }
  int current{end};
  int min{INT_MAX};
  while (current != start) {
    if (graph[previous[current]][current] < min) {
      min = graph[previous[current]][current];
    }
    current = previous[current];
  }

  int actual_maximum{min - guide};
  int trip_count{static_cast<int>(std::ceil(
      static_cast<double>(tourist_count) / actual_maximum))};
  return trip_count;
}

int main() {
  std::string line{};
  int scenario_count{0};
  while (std::getline(std::cin, line)) { // <|V|> <|E|>
    ++scenario_count;
    std::istringstream stream{line};
    int vertices_count{};
    int edge_count{};
    stream >> vertices_count >> edge_count;
    if (vertices_count == 0 && edge_count == 0) {
      break;
    }

    std::vector<std::vector<int>> graph(
        vertices_count, std::vector<int>(vertices_count, -1));
    while (edge_count > 0) {
      std::getline(std::cin, line);
      stream.str(line);
      int start{};
      int end{};
      int maximum_capacity{};
      stream >> start >> end >> maximum_capacity;
      graph[start - 1][end - 1] = maximum_capacity;
      graph[end - 1][start - 1] = maximum_capacity;
      --edge_count;
    }

    std::getline(std::cin, line); // <start> <end> <number of tourists>
    stream.str(line);
    int start{};
    int end{};
    int tourist_count{};
    stream >> start >> end >> tourist_count;

    std::cout << "Scenario #" << scenario_count << '\n'
              << "Minimum Number of Trips = "
              << minimumTrips(graph, start - 1, end - 1, tourist_count)
              << "\n\n";
  }

  return EXIT_SUCCESS;
}
