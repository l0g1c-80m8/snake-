#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, (int) screen_width,
                                (int) screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create surfaces and textures for assets
  obstacle_surface = SDL_LoadBMP("../assets/obstacle.bmp");
  obstacle_texture = SDL_CreateTextureFromSurface(sdl_renderer, obstacle_surface);
  if (nullptr == obstacle_surface || nullptr == obstacle_texture) {
    std::cerr << "Obstacle item could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  speedups_surface = SDL_LoadBMP("../assets/speedup.bmp");
  speedups_texture = SDL_CreateTextureFromSurface(sdl_renderer, speedups_surface);
  if (nullptr == speedups_surface || nullptr == speedups_texture) {
    std::cerr << "Speedup item could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  slowdowns_surface = SDL_LoadBMP("../assets/slowdown.bmp");
  slowdowns_texture = SDL_CreateTextureFromSurface(sdl_renderer, slowdowns_surface);
  if (nullptr == slowdowns_surface || nullptr == slowdowns_texture) {
    std::cerr << "SLowdown item could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  food_surface = SDL_LoadBMP("../assets/food.bmp");
  food_texture = SDL_CreateTextureFromSurface(sdl_renderer, food_surface);
  if (nullptr == food_surface || nullptr == food_texture) {
    std::cerr << "Food item could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(
    std::shared_ptr<Snake> const& snake,
    std::set<SDL_Point> const &obstacles,
    std::set<SDL_Point> const &slowdowns,
    std::set<SDL_Point> const &speedups,
    std::set<SDL_Point> const &food_points
    ) {
  SDL_Rect block;
  block.w = (int) (screen_width / grid_width);
  block.h = (int) (screen_height / grid_height);

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render obstacles
  SDL_SetRenderDrawColor(sdl_renderer, 0x80, 0x00, 0x00, 0xFF);
  for (SDL_Point const &point : obstacles) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderCopy(sdl_renderer, obstacle_texture, nullptr, &block);
  }

  // Render slowdowns
  SDL_SetRenderDrawColor(sdl_renderer, 0x32, 0xCD, 0x32, 0xFF);
  for (SDL_Point const &point : slowdowns) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderCopy(sdl_renderer, slowdowns_texture, nullptr, &block);
  }

  // Render speedups
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x8C, 0x00, 0xFF);
  for (SDL_Point const &point : speedups) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderCopy(sdl_renderer, speedups_texture, nullptr, &block);
  }

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  for (SDL_Point const &point : food_points) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderCopy(sdl_renderer, food_texture, nullptr, &block);
  }

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake -> body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake -> head_x) * block.w;
  block.y = static_cast<int>(snake -> head_y) * block.h;
  if (snake -> alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
