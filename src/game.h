#ifndef GAME_H
#define GAME_H

#include "constant.h"
#include "controller.h"
#include "tetromino.h"
#include "tetromino_manager.h"
#include "tetromino_type.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <array>
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
    Tetromino* mTetromino;
    TetrominoManager mTetrominoManager;

    int init();
    void update();
    void render();
    void draw();
};

#endif
