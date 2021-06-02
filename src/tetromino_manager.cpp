#include "tetromino_manager.h"

TetrominoManager::TetrominoManager()
  : mMersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)))
  , T_block({ { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, colors::LILA)
  , L_block({ { { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, colors::WHITE)
  , J_block({ { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, colors::BLUE)
  , Z_block({ { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } } }, colors::RED)
  , S_block({ { { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } } }, colors::GREEN)
  , O_block({ { { 1, 0 }, { 2, 0 }, { 1, 1 }, { 2, 1 } } }, colors::YELLOW)
  , I_block({ { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } } }, colors::CYAN)
{}

TetrominoManager::~TetrominoManager() {}

Tetromino*
TetrominoManager::get_next_tetromino()
{
  // Improve the choosing of the tetromino. Not all conditions have been applied
  int choice = mDist(mMersenne);
  if (choice == 1) {
    return &Z_block;
  } else if (choice == 2) {
    return &L_block;
  } else if (choice == 3) {
    return &I_block;
  } else if (choice == 4) {
    return &J_block;
  } else if (choice == 5) {
    return &T_block;
  } else if (choice == 5) {
    return &S_block;
  } else {
    return &O_block;
  }
}
