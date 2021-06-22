#ifndef GAME_H
#define GAME_H

#include "color.h"
#include "constant.h"
#include "counter.h"
#include "grid.h"
#include "input.h"
#include "tetromino.h"
#include "tetromino_manager.h"
#include <SDL2/SDL.h>
#include <array>
#include <iostream>

class Game
{
public:
  Game();
  ~Game();

  void gameLoop();

private:
  bool             is_running_;
  bool             in_landing_position;
  SDL_Event        mEvent;
  Input            input_;
  SDL_Window*      mWindow;
  SDL_Renderer*    mRenderer;
  Tetromino*       pTetromino_;
  TetrominoManager mTetrominoManager;
  Grid             grid_;
  Counter          lock_delay_; // Frame until the landed piece locks in position
  Counter          fall_delay_; // Amount of frames to wait till the tetromino falls by one unit

  int              init();
  void             update();
  void             render();
  void             draw();
};

#endif
