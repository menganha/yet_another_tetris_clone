#ifndef GAME_H
#define GAME_H

#include "constant.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "tetramino.h"

class Game
{
  private:
    bool mIsRunning;
    SDL_Event mEvent;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Tetramino mTetramino;

    int init();
    void handleInput();
    void update();
    void render();
    void draw();

  public:
    Game();
    ~Game();

    void gameLoop();
};

#endif
