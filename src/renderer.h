#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "food.hpp"
#include "snake.h"
#include <memory>
#include <vector>

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  // Destructor
  ~Renderer();

  // Copy constructor
  Renderer(const Renderer &other);
  // Copy assignment operator
  Renderer &operator=(const Renderer &other);

  // Move constructor
  Renderer(Renderer &&other) noexcept;
  // Move assignment operator
  Renderer &operator=(Renderer &&other) noexcept;

  void Render(const std::shared_ptr<Snake> &snake,
              const std::shared_ptr<Food> &food);
  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  std::size_t screen_width;
  std::size_t screen_height;
  std::size_t grid_width;
  std::size_t grid_height;
};

#endif