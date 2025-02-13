#ifndef GAME_H
#define GAME_H

#include <random>
#include <fstream>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "type.hpp"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  void Register();
  void SaveScore();


 private:
  Snake snake;
  SDL_Point food;


  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  State state;
  int score;
  std::string name_;

  void PlaceFood();
  void Update(State& running);
};

#endif