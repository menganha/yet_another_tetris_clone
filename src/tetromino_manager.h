#ifndef TETROMINO_MANAGER_H
#define TETROMINO_MANAGER_H

#include "tetromino.h"
#include <SDL2/SDL.h>
#include <ctime>
#include <random>

class TetrominoManager
{
  // Creates tetrominos and manages the random dispatching
public:
  TetrominoManager();
  ~TetrominoManager();

  Tetromino* GetNextTetromino();
  // TODO: Function to call a special rendering function of the tetromino that draws it at
  // the square where it shows the next piece
  void       RenderCachedTetromino(SDL_Renderer* renderer) const;

private:
  std::mt19937                    mMersenne;
  std::uniform_int_distribution<> mDist{ 1, 7 };
  Tetromino*                      cache_;
  Tetromino                       T_block;
  Tetromino                       L_block;
  Tetromino                       J_block;
  Tetromino                       Z_block;
  Tetromino                       S_block;
  Tetromino                       O_block;
  Tetromino                       I_block;
  Tetromino*                      RandomSelection();
};

#endif
