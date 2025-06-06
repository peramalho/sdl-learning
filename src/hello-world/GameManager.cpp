#include "GameManager.h"
#include <SDL3/SDL.h>

GameManager::GameManager()
    : window(nullptr), renderer(nullptr), running(false) {}

GameManager::~GameManager() { cleanup(); }

bool GameManager::initialize() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
    return false;
  }

  if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600,
                                   SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
    SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
    return false;
  }

  running = true;
  return true;
}

void GameManager::render() {
  const char *message{"Hello World!"};
  int w{0}, h{0};
  float x, y;
  const float scale{4.0f};

  // Center the message and scale it up
  SDL_GetRenderOutputSize(renderer, &w, &h);
  SDL_SetRenderScale(renderer, scale, scale);
  x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) /
      2;
  y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

  // Draw the message
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDebugText(renderer, x, y, message);
  SDL_RenderPresent(renderer);
}

void GameManager::cleanup() {}

int GameManager::run() {
  if (!initialize()) {
    return -1;
  }

  while (running) {
    render();

    SDL_Delay(16); // 60 FPS
  }

  return 0;
}