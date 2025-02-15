#ifndef ASTAR_H
#define ASTAR_H

#include <string>
#include <vector>

class AStar {
public:
  AStar(std::size_t grid_width, std::size_t grid_height);

  struct Cell {
    int x;
    int y;
  };

  enum class State { kEmpty, kClosed, kPath, kStart, kFinish };

  std::vector<std::string> Search(const Cell &start, const Cell &goal);

private:
  std::vector<std::vector<State>> grid;

  std::vector<Cell> delta = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  int Heuristic(int x1, int y1, int x2, int y2);

  void AddToOpen(int x, int y, int g, int h,
                 std::vector<std::vector<int>> &openlist,
                 std::vector<std::vector<State>> &grid);

  static bool Compare(const std::vector<int> &a, const std::vector<int> &b);

  void CellSort(std::vector<std::vector<int>> *v);

  bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid);

  std::string CellString(State cell);

  void PrintGrid(const std::vector<std::vector<State>> grid);

  void ExpandNeighbors(const std::vector<int> &current, Cell goal,
                       std::vector<std::vector<int>> &openlist,
                       std::vector<std::vector<State>> &grid);

  std::vector<std::string> GetDirections();
};

#endif // ASTAR_H