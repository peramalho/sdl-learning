#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SDL3/SDL.h>

class GameManager {

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;

public:
  GameManager();
  ~GameManager();

  int run();
  void cleanup();
};

#endif // GAME_MANAGER_H