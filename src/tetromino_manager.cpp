#include "tetromino_manager.h"

TetrominoManager::TetrominoManager()
  : mMersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)))
  , cache_{ nullptr }
  , T_block(tdata::TetrominoType::T_block, colors::LILA)
  , L_block(tdata::TetrominoType::L_block, colors::WHITE)
  , J_block(tdata::TetrominoType::J_block, colors::BLUE)
  , Z_block(tdata::TetrominoType::Z_block, colors::RED)
  , S_block(tdata::TetrominoType::S_block, colors::GREEN)
  , O_block(tdata::TetrominoType::O_block, colors::YELLOW)
  , I_block(tdata::TetrominoType::I_block, colors::CYAN)
{
  cache_ = RandomSelection();
}

TetrominoManager::~TetrominoManager() {}

Tetromino*
TetrominoManager::GetNextTetromino()
{
  Tetromino* current = cache_;
  cache_ = RandomSelection();
  return current;
}

Tetromino*
TetrominoManager::RandomSelection()
{
  // TODO: Use the seven bag approach of the official tetris game to make it less random
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
  } else if (choice == 6) {
    return &S_block;
  } else {
    return &O_block;
  }
}
