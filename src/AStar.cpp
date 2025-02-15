#include "AStar.hpp"
#include <algorithm>
#include <iostream>
#include <math.h>

AStar::AStar(std::size_t grid_width, std::size_t grid_height) {
  // Initialize the grid state kEmpty
  grid.resize(grid_width, std::vector<State>(grid_height, State::kEmpty));
}

bool AStar::Compare(const std::vector<int> &a, const std::vector<int> &b) {
  int f1 = a[2] + a[3]; // f1 = g1 + h1
  int f2 = b[2] + b[3]; // f2 = g2 + h2
  return f1 > f2;
}

void AStar::CellSort(std::vector<std::vector<int>> *v) {
  std::sort(v->begin(), v->end(), Compare);
}

int AStar::Heuristic(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

void AStar::AddToOpen(int x, int y, int g, int h,
                      std::vector<std::vector<int>> &openlist,
                      std::vector<std::vector<State>> &grid) {
  // Add node to open vector, and mark grid cell as closed.
  openlist.push_back(std::vector<int>{x, y, g, h});
  grid[x][y] = State::kClosed;
}

bool AStar::CheckValidCell(int x, int y,
                           std::vector<std::vector<State>> &grid) {
  bool on_grid_x = (x >= 0 && x < grid.size());
  bool on_grid_y = (y >= 0 && y < grid[0].size());
  if (on_grid_x && on_grid_y)
    return grid[x][y] == State::kEmpty;
  return false;
}

void AStar::ExpandNeighbors(const std::vector<int> &current, Cell goal,
                            std::vector<std::vector<int>> &openlist,
                            std::vector<std::vector<State>> &grid) {
  // Get current node's data.
  int x = current[0];
  int y = current[1];
  int g = current[2];

  // Loop through current node's potential neighbors.
  for (const auto &d : delta) {
    int x2 = x + d.x;
    int y2 = y + d.y;

    // Check that the potential neighbor's x2 and y2 values are on the grid and
    // not closed.
    if (CheckValidCell(x2, y2, grid)) {
      // Increment g value and add neighbor to open list.
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goal.x, goal.y);
      AddToOpen(x2, y2, g2, h2, openlist, grid);
    }
  }
}

std::vector<std::string> AStar::Search(const Cell &start, const Cell &goal) {
  // Create the vector of open nodes.
  std::vector<std::vector<int>> open{};

  // Initialize the starting node.
  int x = start.x;
  int y = start.y;
  int g = 0;
  int h = Heuristic(x, y, goal.x, goal.y);
  AddToOpen(x, y, g, h, open, grid);

  while (open.size() > 0) {
    // Get the next node
    CellSort(&open);
    auto current = open.back();
    open.pop_back();
    x = current[0];
    y = current[1];
    grid[x][y] = State::kPath;

    // Check if we're done.
    if (x == goal.x && y == goal.y) {
      grid[start.x][start.y] = State::kStart;
      grid[x][y] = State::kFinish;
      break;
    }

    // If we're not done, expand search to current node's neighbors.
    ExpandNeighbors(current, goal, open, grid);
  }
  PrintGrid(grid);

  return GetDirections();
}

std::string AStar::CellString(State cell) {
  switch (cell) {
  case State::kPath:
    return "🐍  ";
  case State::kStart:
    return "🏁  ";
  case State::kFinish:
    return "🚦  ";
  default:
    return "0   ";
  }
}

void AStar::PrintGrid(const std::vector<std::vector<State>> grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      std::cout << CellString(grid[i][j]);
    }
    std::cout << "\n";
  }
}

std::vector<std::string> AStar::GetDirections() {
  std::vector<std::string> directions;

  std::size_t grid_width = grid.size();
  if (grid_width == 0)
    return directions;
  std::size_t grid_height = grid[0].size();

  // Find the start cell.
  int start_x = -1, start_y = -1;
  for (std::size_t i = 0; i < grid_width; ++i) {
    for (std::size_t j = 0; j < grid_height; ++j) {
      if (grid[i][j] == State::kStart) {
        start_x = i;
        start_y = j;
        break;
      }
    }
    if (start_x != -1)
      break;
  }
  if (start_x == -1) {
    std::cerr << "Error: Start cell not found in grid.\n";
    return directions;
  }

  // Start traversing from the start cell.
  int current_x = start_x;
  int current_y = start_y;
  int prev_x = -1;
  int prev_y = -1;

  // Walk until reaching the finish cell.
  while (grid[current_x][current_y] != State::kFinish) {
    bool foundNext = false;
    // Check all four directions.
    std::vector<std::pair<std::pair<int, int>, std::string>> neighbors = {
        {{current_x - 1, current_y}, "UP"},
        {{current_x + 1, current_y}, "DOWN"},
        {{current_x, current_y - 1}, "LEFT"},
        {{current_x, current_y + 1}, "RIGHT"}};

    for (auto &nb : neighbors) {
      int nx = nb.first.first;
      int ny = nb.first.second;

      if (nx < 0 || nx >= static_cast<int>(grid_width) || ny < 0 ||
          ny >= static_cast<int>(grid_height))
        continue;

      // Avoid going back to the previous cell.
      if (nx == prev_x && ny == prev_y)
        continue;

      // Follow if this neighbor is part of the path or is the finish.
      if (grid[nx][ny] == State::kPath || grid[nx][ny] == State::kFinish) {
        directions.push_back(nb.second);
        prev_x = current_x;
        prev_y = current_y;
        current_x = nx;
        current_y = ny;
        foundNext = true;
        break;
      }
    }

    if (!foundNext) {
      std::cerr << "Error: Broken path at (" << current_x << ", " << current_y
                << ").\n";
      break;
    }
  }

  return directions;
}