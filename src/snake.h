#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        speed(0.1),
        size(1),
        alive(true),
        growing(false) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y) const;
  bool ObstacleCell(int x, int y) const;

  Direction direction = Direction::kUp;

  float speed;
  int size;
  bool alive;
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing;
  int grid_width;
  int grid_height;
};

#endif