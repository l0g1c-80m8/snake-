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

  void Render(
      std::shared_ptr<Snake> const& snake,
      std::set<SDL_Point> const &obstacles,
      std::set<SDL_Point> const &slowdowns,
      std::set<SDL_Point> const &speedups,
      std::set<SDL_Point> const &food_points
      ) const;
  void UpdateWindowTitle(int score, int fps);

 private:
  class SDL_Resources {
  private:
      SDL_Window *sdl_window;
      SDL_Renderer *sdl_renderer{};
      std::unique_ptr<SDL_Surface> obstacle_surface;
      SDL_Texture *obstacle_texture{};
      std::unique_ptr<SDL_Surface> speedups_surface;
      SDL_Texture *speedups_texture{};
      std::unique_ptr<SDL_Surface> slowdowns_surface;
      SDL_Texture *slowdowns_texture{};
      std::unique_ptr<SDL_Surface> food_surface;
      SDL_Texture *food_texture{};

  public:
      SDL_Resources(
          std::size_t screen_width,
          std::size_t screen_height,
          std::size_t grid_width,
          std::size_t grid_height
          );
      ~SDL_Resources();
      SDL_Window* getSDL_Window();
      SDL_Renderer* getSDL_Renderer();
      SDL_Texture *getObstacleTexture();
      SDL_Texture *getSlowdownTexture();
      SDL_Texture *getSpeedupTexture();
      SDL_Texture *getFoodTexture();
  };

  std::unique_ptr<SDL_Resources> sdl_resources;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif