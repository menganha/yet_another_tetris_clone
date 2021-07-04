#ifndef TETROMINO_MANAGER_H
#define TETROMINO_MANAGER_H

#include "tetromino.h"
#include <random>

class TetrominoManager
{
  // Creates Tetrominos and manages the random dispatching
public:
  TetrominoManager();
  ~TetrominoManager();

  Tetromino* GetNextTetromino();
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
