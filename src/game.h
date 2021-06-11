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
  bool             is_running_;
  bool             tetromino_landed_;
  SDL_Event        mEvent;
  Input            input_;
  SDL_Window*      mWindow;
  SDL_Renderer*    mRenderer;
  Tetromino*       pTetromino_;
  TetrominoManager mTetrominoManager;
  Grid             grid_;
  Counter          fall_delay_{ 50 }; // Amount of frames to wait till the
                                      // tetromino falls by one unit
  Counter lock_delay_{ 10 }; // Frame until the landed piece locks in position

  int     init();
  void    update();
  void    render();
  void    draw();
};

#endif
