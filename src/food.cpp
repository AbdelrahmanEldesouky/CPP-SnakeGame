#include "food.hpp"

Food::Food(std::size_t grid_width, std::size_t grid_height) 
            : x_(0), y_(0), 
            engine(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count())),
            random_w(0, static_cast<int>(grid_width - 1)),
            random_h(0, static_cast<int>(grid_height - 1)) {}

int Food::GetX() const { return x_; }
int Food::GetY() const { return y_; }

void Food::PlaceFood(const Snake &snake)
{
    int x_random, y_random;
    while (true)
    {
        x_random = random_w(engine);
        y_random = random_h(engine);
        // Check that the location is not occupied by a snake item before placing
        // food.
        if (!snake.SnakeCell(x_random, y_random) && !snake.ObstacleCell(x_random, y_random))
        {
            x_ = x_random;
            y_ = y_random;
            return;
        }
    }
}