#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <random>
#include <chrono>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "snake.h"
#include "SDL.h"
#include "type.hpp"

class Food
{
public:
    Food(std::size_t grid_width, std::size_t grid_height);

    enum class FoodType
    {
        kGrow,
        kBonus
    };

    int GetX() const;
    int GetY() const;

    int GetBonusX() const; 
    int GetBonusY() const;
    bool IsBonusActive() const;

    void PlaceFood(const std::shared_ptr<Snake> &snake);
    void PlaceBonusFood(const std::shared_ptr<Snake> &snake);

    void StartBonusFoodTimer();

    void ClearBonusFood();

    FoodType GetFood(SDL_Rect const &block) const;

private:
    int x_;
    int y_;

    int bonus_x_;
    int bonus_y_;

    bool is_bonus_food_active_;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    std::thread bonus_food_timer_;
    std::mutex bonus_food_mutex_;
    std::condition_variable bonus_cv_;

    void BonusFoodTimer();
};

#endif // FOOD_H