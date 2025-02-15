#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height),
      grid_width(grid_width), grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

Renderer::Renderer(const Renderer &other) {
  screen_width = other.screen_width;
  screen_height = other.screen_height;
  grid_width = other.grid_width;
  grid_height = other.grid_height;
  sdl_window = other.sdl_window;
  sdl_renderer = other.sdl_renderer;
}

Renderer &Renderer::operator=(const Renderer &other) {
  if(this == &other) {
    return *this;
  }
  screen_width = other.screen_width;
  screen_height = other.screen_height;
  grid_width = other.grid_width;
  grid_height = other.grid_height;
  sdl_window = other.sdl_window;
  sdl_renderer = other.sdl_renderer;
  return *this;
}

Renderer::Renderer(Renderer &&other) noexcept {
  sdl_window = other.sdl_window;
  sdl_renderer = other.sdl_renderer;
  screen_width = other.screen_width;
  screen_height = other.screen_height;
  grid_width = other.grid_width;
  grid_height = other.grid_height;

  other.sdl_window = nullptr;
  other.sdl_renderer = nullptr;
  other.screen_width = 0;
  other.screen_height = 0;
  other.grid_width = 0;
  other.grid_height = 0;
}

Renderer &Renderer::operator=(Renderer &&other) noexcept {
  if(this == &other) {
    return *this;
  }

  if (sdl_renderer) {
    SDL_DestroyRenderer(sdl_renderer);
  }
  if (sdl_window) {
    SDL_DestroyWindow(sdl_window);
  }
  
  sdl_window = other.sdl_window;
  sdl_renderer = other.sdl_renderer;
  screen_width = other.screen_width;
  screen_height = other.screen_height;
  grid_width = other.grid_width;
  grid_height = other.grid_height;

  other.sdl_window = nullptr;
  other.sdl_renderer = nullptr;
  other.screen_width = 0;
  other.screen_height = 0;
  other.grid_width = 0;
  other.grid_height = 0;
  
  return *this;
}

void Renderer::Render(const std::shared_ptr<Snake> &snake,
                      const std::shared_ptr<Food> &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food->GetX() * block.w;
  block.y = food->GetY() * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render Wall around window (Color light green)
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
  for (int i = 0; i < grid_width; ++i) {
    block.x = i * block.w;
    block.y = 0;
    SDL_RenderFillRect(sdl_renderer, &block);
    block.y = (grid_height - 1) * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  for (int i = 0; i < grid_height; ++i) {
    block.x = 0;
    block.y = i * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
    block.x = (grid_width - 1) * block.w;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
