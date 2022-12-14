#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <memory>

class Controller {
 public:
  static void HandleInput(bool &running, std::shared_ptr<Snake> &snake) ;

 private:
  static void ChangeDirection(std::shared_ptr<Snake> &snake, Snake::Direction input, Snake::Direction opposite);
};

#endif