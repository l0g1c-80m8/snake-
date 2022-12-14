#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <set>
#include "SDL.h"
#include "config.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  enum class GridItemType { giObstacle, giSlowdown, giSpeedup, giFood };
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  [[nodiscard]] int GetScore() const;
  [[nodiscard]] int GetSlowdowns() const;
  [[nodiscard]] int GetSpeedups() const;
  [[nodiscard]] int GetSize() const;

 private:
  std::shared_ptr<Snake> snake;
  std::shared_ptr<Config> config;
  std::set<SDL_Point> obstacles;
  std::set<SDL_Point> slowdowns;
  std::set<SDL_Point> speedups;
  std::set<SDL_Point> food_points;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int slow_downs{0};
  int speed_ups{0};

  void PlaceGridItem(SDL_Point gridPoint, Game::GridItemType itemType = Game::GridItemType::giFood);
  void Update();
  std::set<SDL_Point> GenerateGridPoints(int num);
  SDL_Point GenerateGridPoint();
};

#endif