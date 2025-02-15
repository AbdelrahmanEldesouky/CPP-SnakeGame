#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "snake.h"
#include "type.hpp"

class Controller {
 public:
  void HandleInput(State &state, std::shared_ptr<Snake> &snake) const;

 private:
  void ChangeDirection(std::shared_ptr<Snake> &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif