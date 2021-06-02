#ifndef GAME_H
#define GAME_H

#include "color.h"
#include "constant.h"
#include "controller.h"
#include "grid.h"
#include "tetromino.h"
#include "tetromino_manager.h"
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
  bool             mIsRunning;
  SDL_Event        mEvent;
  Controller       mController;
  SDL_Window*      mWindow;
  SDL_Renderer*    mRenderer;
  Tetromino*       mTetromino;
  TetrominoManager mTetrominoManager;
  Grid             mGrid;

  int              init();
  void             update();
  void             render();
  void             draw();
};

#endif
