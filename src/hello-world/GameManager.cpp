#include "GameManager.h"

GameManager::GameManager()
    : window(nullptr), renderer(nullptr), running(false) {}

GameManager::~GameManager() { cleanup(); }

void GameManager::cleanup() {}

bool GameManager::initialize() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
    return false;
  }

  if (!SDL_CreateWindowAndRenderer("HEllo World", 800, 600,
                                   SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
    SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
    return false;
  }

  running = true;
  return true;
}

int GameManager::run() {
  if (!initialize()) {
    return -1;
  }
  return 0;
}