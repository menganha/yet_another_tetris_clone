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
#include <SDL2/SDL_ttf.h>
#include <array>
#include "user_interface.h"
#include <iostream>
#include <string>

class Game
{
public:
  Game();
  ~Game();

  void RunLoop();
  void Restart();

private:
  bool             game_over_;
  bool             is_running_;
  int              score_;
  int              level_;
  Input            input_;
  UserInterface    ui;
  SDL_Window*      window_;
  SDL_Renderer*    renderer_;
  Tetromino*       pTetromino_;
  TetrominoManager mTetrominoManager;
  Grid             grid_;
  Counter          lock_delay_; // Frame until the landed piece locks in position
  Counter          fall_delay_; // Amount of frames to wait till the tetromino falls by one unit

  int              Init();
  void             Update();
  void             Render();
  void             Draw();
  int              ClearedRowsToScore(int const cleared_rows) const;
  void             HandleGameOver();
};

#endif
