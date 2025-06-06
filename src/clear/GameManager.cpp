#include "GameManager.h"
#include <SDL3/SDL.h>
#include <string>

constexpr const char *APP_NAME{"Clear"};
constexpr const char *APP_VERSION{"1.0.0"};
constexpr const char *APP_IDENTIFIER{"com.clear"};
constexpr int WINDOW_WIDTH{800};
constexpr int WINDOW_HEIGHT{600};
constexpr int TARGET_FPS{60};
constexpr int FRAME_DELAY_MS{1000 / TARGET_FPS};

GameManager::GameManager()
    : window(nullptr), renderer(nullptr), running(false) {}

GameManager::~GameManager() { cleanup(); }

bool GameManager::initialize() {
  SDL_SetAppMetadata(APP_NAME, APP_VERSION, APP_IDENTIFIER);

  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
    return false;
  }

  if (!SDL_CreateWindowAndRenderer(APP_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                   &window, &renderer)) {
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
  const double now = ((double)SDL_GetTicks()) /
                     1000.0; /* convert from milliseconds to seconds. */
  /* choose the color for the frame we will draw. The sine wave trick makes it
   * fade between colors smoothly. */
  const float red = (float)(0.5 + 0.5 * SDL_sin(now));
  const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
  const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
  SDL_SetRenderDrawColorFloat(
      renderer, red, green, blue,
      SDL_ALPHA_OPAQUE_FLOAT); /* new color, full alpha. */

  /* clear the window to the draw color. */
  SDL_RenderClear(renderer);

  /* put the newly-cleared rendering on the screen. */
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