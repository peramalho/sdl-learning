#include "GameManager.h"

GameManager::GameManager()
    : window(nullptr), renderer(nullptr), running(false) {}

GameManager::~GameManager() { cleanup(); }

void GameManager::cleanup() {}

int GameManager::run() { return 0; }