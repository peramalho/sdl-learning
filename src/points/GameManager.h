#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SDL3/SDL.h>

constexpr const char *APP_NAME{"Points"};
constexpr const char *APP_VERSION{"1.0.0"};
constexpr const char *APP_IDENTIFIER{"com.points"};
constexpr int WINDOW_WIDTH{800};
constexpr int WINDOW_HEIGHT{600};
constexpr int TARGET_FPS{60};
constexpr int FRAME_DELAY_MS{1000 / TARGET_FPS};
constexpr float FRAME_DELAY_S{(float)FRAME_DELAY_MS / 1000};

constexpr int NUM_POINTS{500};
constexpr int MIN_PIXELS_PER_SECOND{
    30}; /* move at least this many pixels per second. */
constexpr int MAX_PIXELS_PER_SECOND{
    60}; /* move this many pixels per second at most. */

class GameManager {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;
  SDL_FPoint points[NUM_POINTS];
  float point_speeds[NUM_POINTS];

  bool initialize();
  void handleEvents();
  void update();
  void render();
  void cleanup();

public:
  GameManager();
  ~GameManager();

  int run();
};

#endif // GAME_MANAGER_H