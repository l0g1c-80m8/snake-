#include "renderer.h"
#include "resources.h"
#include <iostream>
#include <memory>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  sdl_resources = std::make_unique<Renderer::SDL_Resources>(screen_width, screen_height, grid_width, grid_height);
}

Renderer::~Renderer() = default;

void Renderer::Render(
    std::shared_ptr<Snake> const& snake,
    std::set<SDL_Point> const &obstacles,
    std::set<SDL_Point> const &slowdowns,
    std::set<SDL_Point> const &speedups,
    std::set<SDL_Point> const &food_points
    ) const {
  SDL_Rect block;
  block.w = (int) (screen_width / grid_width);
  block.h = (int) (screen_height / grid_height);

  // Clear screen
  SDL_SetRenderDrawColor(sdl_resources->GetSDL_Renderer(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_resources->GetSDL_Renderer());

  // Render obstacles
  SDL_SetRenderDrawColor(sdl_resources->GetSDL_Renderer(), 0x80, 0x00, 0x00, 0xFF);
  for (SDL_Point const &point : obstacles) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderCopy(sdl_resources->GetSDL_Renderer(), sdl_resources->GetObstacleTexture(), nullptr, &block);
  }

  // Render slowdowns
  SDL_SetRenderDrawColor(sdl_resources->GetSDL_Renderer(), 0x32, 0xCD, 0x32, 0xFF);
  for (SDL_Point const &point : slowdowns) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderCopy(sdl_resources->GetSDL_Renderer(), sdl_resources->GetSlowdownTexture(), nullptr, &block);
  }

  // Render speedups
  SDL_SetRenderDrawColor(sdl_resources->GetSDL_Renderer(), 0xFF, 0x8C, 0x00, 0xFF);
  for (SDL_Point const &point : speedups) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderCopy(sdl_resources->GetSDL_Renderer(), sdl_resources->GetSpeedupTexture(), nullptr, &block);
  }

  // Render food
  SDL_SetRenderDrawColor(sdl_resources->GetSDL_Renderer(), 0xFF, 0xCC, 0x00, 0xFF);
  for (SDL_Point const &point : food_points) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderCopy(sdl_resources->GetSDL_Renderer(), sdl_resources->GetFoodTexture(), nullptr, &block);
  }

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_resources->GetSDL_Renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake -> body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_resources->GetSDL_Renderer(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake -> head_x) * block.w;
  block.y = static_cast<int>(snake -> head_y) * block.h;
  if (snake -> alive) {
    SDL_SetRenderDrawColor(sdl_resources->GetSDL_Renderer(), 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_resources->GetSDL_Renderer(), 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_resources->GetSDL_Renderer(), &block);

  // Update Screen
  SDL_RenderPresent(sdl_resources->GetSDL_Renderer());
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_resources->GetSDL_Window(), title.c_str());
}

Renderer::SDL_Resources::SDL_Resources(
    const std::size_t screen_width,
    const std::size_t screen_height,
    const std::size_t grid_width,
    const std::size_t grid_height
    ) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow(
      "Snake Game", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      (int) screen_width,
      (int) screen_height,
      SDL_WINDOW_SHOWN
      );
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
  obstacle_surface.reset(SDL_LoadBMP(obstacle_asset));
  obstacle_texture = SDL_CreateTextureFromSurface(sdl_renderer, obstacle_surface.get());
  if (nullptr == obstacle_surface || nullptr == obstacle_texture) {
    std::cerr << "Obstacle item could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  speedups_surface.reset(SDL_LoadBMP(speedup_asset));
  speedups_texture = SDL_CreateTextureFromSurface(sdl_renderer, speedups_surface.get());
  if (nullptr == speedups_surface || nullptr == speedups_texture) {
    std::cerr << "Speedup item could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  slowdowns_surface.reset(SDL_LoadBMP(slowdown_asset));
  slowdowns_texture = SDL_CreateTextureFromSurface(sdl_renderer, slowdowns_surface.get());
  if (nullptr == slowdowns_surface || nullptr == slowdowns_texture) {
    std::cerr << "SLowdown item could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  food_surface.reset(SDL_LoadBMP(food_asset));
  food_texture = SDL_CreateTextureFromSurface(sdl_renderer, food_surface.get());
  if (nullptr == food_surface || nullptr == food_texture) {
    std::cerr << "Food item could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

}

Renderer::SDL_Resources::~SDL_Resources() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyTexture(obstacle_texture);
  SDL_DestroyTexture(speedups_texture);
  SDL_DestroyTexture(slowdowns_texture);
  SDL_DestroyTexture(food_texture);
  SDL_Quit();
}

SDL_Window* Renderer::SDL_Resources::GetSDL_Window() { return sdl_window; }
SDL_Renderer* Renderer::SDL_Resources::GetSDL_Renderer() { return sdl_renderer; }
SDL_Texture* Renderer::SDL_Resources::GetObstacleTexture() { return obstacle_texture; }
SDL_Texture* Renderer::SDL_Resources::GetSlowdownTexture() { return slowdowns_texture; }
SDL_Texture* Renderer::SDL_Resources::GetSpeedupTexture() { return speedups_texture; }
SDL_Texture* Renderer::SDL_Resources::GetFoodTexture() { return food_texture; }