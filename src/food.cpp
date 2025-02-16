#include "food.hpp"

Food::Food(std::size_t grid_width, std::size_t grid_height)
    : x_(0), y_(0), bonus_x_(-1), bonus_y_(-1), is_bonus_food_active_(false),
      engine(static_cast<unsigned>(
          std::chrono::steady_clock::now().time_since_epoch().count())),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {}

int Food::GetX() const { return x_; }
int Food::GetY() const { return y_; }

int Food::GetBonusX() const { return bonus_x_; }
int Food::GetBonusY() const { return bonus_y_; }

bool Food::IsBonusActive() const { return is_bonus_food_active_; }

Food::FoodType Food::GetFood(SDL_Rect const &block) const {
  if (is_bonus_food_active_ && block.x == bonus_x_ && block.y == bonus_y_) {
    return FoodType::kBonus;
  }
  return FoodType::kGrow;
}

void Food::PlaceFood(const std::shared_ptr<Snake> &snake) {
  int x_random, y_random;
  while (true) {
    x_random = random_w(engine);
    y_random = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->SnakeCell(x_random, y_random) &&
        !snake->ObstacleCell(x_random, y_random)) {
      x_ = x_random;
      y_ = y_random;
      return;
    }
  }
}

void Food::PlaceBonusFood(const std::shared_ptr<Snake> &snake) {
  int x_random, y_random;
  while (true) {
    x_random = random_w(engine);
    y_random = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->SnakeCell(x_random, y_random) &&
        !snake->ObstacleCell(x_random, y_random)) {
      bonus_x_ = x_random;
      bonus_y_ = y_random;
      is_bonus_food_active_ = true;
      std::cout << "Bonus food placed at: " << bonus_x_ << ", " << bonus_y_
                << std::endl;
      return;
    }
  }
}

void Food::StartBonusFoodTimer() {
  bonus_food_timer_ = std::thread(&Food::BonusFoodTimer, this);
  bonus_food_timer_.detach();
}

void Food::ClearBonusFood() {
  std::unique_lock<std::mutex> lock(bonus_food_mutex_);
  is_bonus_food_active_ = false;
  bonus_x_ = -1;
  bonus_y_ = -1;
}

void Food::BonusFoodTimer() {
  const int bonusSeconds = 5;
  auto startTime = std::chrono::high_resolution_clock::now();
  std::unique_lock<std::mutex> lock(bonus_food_mutex_);
  while (is_bonus_food_active_) {
    lock.unlock();
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(
                              currentTime - startTime)
                              .count();
    if (elapsedSeconds >= bonusSeconds) {
      // Bonus food time is up; remove bonus food from the board.
      is_bonus_food_active_ = false;
      bonus_x_ = -1;
      bonus_y_ = -1;
      break;
    }
    lock.lock();
    bonus_cv_.wait_for(lock, std::chrono::milliseconds(800));
  }
}