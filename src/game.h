#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "type.hpp"
#include "food.hpp"

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
  Food food;

  State state;
  int score;
  std::string name_;
  int frame_count;

  std::mutex renderer_mutex;

  void Update(State& state);
  void UpdateWindowTitle(Renderer &renderer);
};

#endif