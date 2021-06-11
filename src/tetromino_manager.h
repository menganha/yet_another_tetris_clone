#ifndef TETROMINO_MANAGER_H
#define TETROMINO_MANAGER_H

#include "tetromino.h"
#include <ctime>
#include <random>

class TetrominoManager
{
  // Creates tetrominos and manages the random dispatching
public:
  TetrominoManager();
  ~TetrominoManager();

  Tetromino* get_next_tetromino();

private:
  std::mt19937 mMersenne;
  std::uniform_int_distribution<> mDist{ 1, 7 };
  Tetromino T_block;
  Tetromino L_block;
  Tetromino J_block;
  Tetromino Z_block;
  Tetromino S_block;
  Tetromino O_block;
  Tetromino I_block;
};

#endif
