#ifndef TETROMINO_MANAGER_H
#define TETROMINO_MANAGER_H

#include "tetromino.h"
#include "tetromino_creator.h"
#include "tetromino_type.h"
#include <ctime>
#include <random>

class TetrominoManager
{
public:
  TetrominoManager();
  ~TetrominoManager();

  Tetromino* get_next_tetromino();

private:
  std::mt19937 mMersenne;
  std::uniform_int_distribution<> mDist{ 1, 7 };
  Tetromino* L_block;
  Tetromino* J_block;
  Tetromino* T_block;
  Tetromino* S_block;
  Tetromino* Z_block;
  Tetromino* O_block;
  Tetromino* I_block;
};

#endif
