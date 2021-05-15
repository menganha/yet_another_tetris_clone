#ifndef GAME_H
#define GAME_H

#include "constant.h"
#include "controller.h"
#include "tetramino.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game
{
  public:
    Game();
    ~Game();

    void gameLoop();

  private:
    bool mIsRunning;
    SDL_Event mEvent;
    Controller mController;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Tetramino mTetramino;

    int init();
    void update();
    void render();
    void draw();
};

#endif
