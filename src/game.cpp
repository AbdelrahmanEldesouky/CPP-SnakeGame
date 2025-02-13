#include "game.h"
#include "SDL.h"
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      food(grid_width, grid_height),
      state(State::kRunning),
      score(0), name_("")
{
  food.PlaceFood(snake);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while (state != State::kExit) {
    // We continue looping as long as the game is running.

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(state, snake);

    // Update only if the game is running
    if (state == State::kRunning) {
      Update(state);
    }
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update(State &state) {
  if (!snake.alive) {
    state = State::kExit;
    return;
  }

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.GetX() == new_x && food.GetY() == new_y) {
    score++;
    food.PlaceFood(snake);
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::Register() {
  std::cout << "Snake Game\n\n";
  std::cout << "Please Enter Your Name: ";
  std::getline(std::cin, name_);

  std::ifstream file = std::ifstream(name_ + ".txt");

  if (file.is_open()) {
    // Get HighScore and Welcome Message
    std::string highscore;

    // Get High Score
    int highscore_int = 0;
    while (std::getline(file, highscore)) {
      if (highscore_int < std::stoi(highscore)) {
        highscore_int = std::stoi(highscore);
      }
    }

    std::cout << "Welcome Back " << name_ << "\n";
    std::cout << "High Score: " << highscore_int << "\n";
  } else {
    // Create a new file
    std::ofstream file = std::ofstream(name_ + ".txt");

    std::cout << "Welcome " << name_ << "\n";
  }
}

void Game::SaveScore() {
  std::ofstream file;
  file.open(name_ + ".txt", std::ios::app);
  file << score << std::endl;
}