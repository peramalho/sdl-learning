#include "GameManager.h"
#include <SDL3/SDL.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int TARGET_FPS = 60;
constexpr int FRAME_DELAY_MS = 1000 / TARGET_FPS;

GameManager::GameManager()
    : window(nullptr), renderer(nullptr), running(false) {}

GameManager::~GameManager() { cleanup(); }

bool GameManager::initialize() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
    return false;
  }

  if (!SDL_CreateWindowAndRenderer("Hello World", WINDOW_WIDTH, WINDOW_HEIGHT,
                                   SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
    SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
    return false;
  }

  running = true;
  return true;
}

void GameManager::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_QUIT) {
      running = false;
    }
  }
}

void GameManager::update() {
  // Game logic will go here
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

void GameManager::cleanup() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }
  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
  SDL_Quit();
}

int GameManager::run() {
  if (!initialize()) {
    return -1;
  }

  while (running) {
    handleEvents();
    update();
    render();
    SDL_Delay(FRAME_DELAY_MS);
  }

  return 0;
}