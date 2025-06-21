#include "GameManager.h"
#include <SDL3/SDL.h>

GameManager::GameManager()
    : window(nullptr), renderer(nullptr), running(false) {}

GameManager::~GameManager() { cleanup(); }

bool GameManager::initialize() {
  int i;

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

  for (i = 0; i < SDL_arraysize(points); i++) {
    points[i].x = SDL_randf() * ((float)WINDOW_WIDTH);
    points[i].y = SDL_randf() * ((float)WINDOW_HEIGHT);
    point_speeds[i] =
        MIN_PIXELS_PER_SECOND +
        (SDL_randf() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND));
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
  int i;
  for (i = 0; i < SDL_arraysize(points); i++) {
    const float distance = FRAME_DELAY_MS * point_speeds[i];
    // move all points for a new frame
    points[i].x += distance;
    points[i].y += distance;
    if ((points[i].x >= WINDOW_WIDTH) || (points[i].y >= WINDOW_HEIGHT)) {
      // reset point at a when off the screen
      if (SDL_rand(2)) {
        points[i].x = SDL_randf() * ((float)WINDOW_WIDTH);
        points[i].y = 0.0f;
      } else {
        points[i].x = 0.0f;
        points[i].y = SDL_randf() * ((float)WINDOW_HEIGHT);
      }
      point_speeds[i] =
          MIN_PIXELS_PER_SECOND +
          (SDL_randf() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND));
    }
  }
}

void GameManager::render() {
  int w{0}, h{0};
  float x, y;
  const float scale{4.0f};

  // Center the message and scale it up
  SDL_GetRenderOutputSize(renderer, &w, &h);

  // Draw the message
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderPoints(renderer, points,
                   SDL_arraysize(points)); /* draw all the points! */
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