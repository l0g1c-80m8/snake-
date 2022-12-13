#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <set>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height);
  ~Renderer();

  void Render(std::shared_ptr<Snake> const& snake, std::set<SDL_Point> const &food_points);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif