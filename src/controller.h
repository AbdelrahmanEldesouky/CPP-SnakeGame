#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "type.hpp"

class Controller {
 public:
  void HandleInput(State &state, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif