#ifndef SNAKE_H
#define SNAKE_H

#include <memory>
#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  static std::shared_ptr<Snake> Instance(int grid_width, int grid_height);

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
    Snake(int grid_width, int grid_height)
            : grid_width(grid_width),
              grid_height(grid_height),
              head_x(static_cast<float>(grid_width) / 2),
              head_y(static_cast<float>(grid_height) / 2) {}

  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  inline static std::shared_ptr<Snake> _instance;
  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif