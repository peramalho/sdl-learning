#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SDL3/SDL.h>

class GameManager {

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;
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