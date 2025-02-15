#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <random>
#include <chrono>
#include <memory>
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
        kShrink
    };

    int GetX() const;
    int GetY() const;

    void PlaceFood(const std::shared_ptr<Snake> &snake);
    FoodType GetFood(SDL_Rect const &block) const;

private:
    int x_;
    int y_;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
};

#endif // FOOD_H