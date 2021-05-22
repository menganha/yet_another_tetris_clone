#include "tetromino_manager.h"

TetrominoManager::TetrominoManager()
  : mMersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) }
{
  L_block = TetrominoCreator::create_block(tetrominoType::L_block);
  J_block = TetrominoCreator::create_block(tetrominoType::J_block);
  T_block = TetrominoCreator::create_block(tetrominoType::T_block);
  S_block = TetrominoCreator::create_block(tetrominoType::S_block);
  Z_block = TetrominoCreator::create_block(tetrominoType::Z_block);
  O_block = TetrominoCreator::create_block(tetrominoType::O_block);
  I_block = TetrominoCreator::create_block(tetrominoType::I_block);
}

TetrominoManager::~TetrominoManager() {}

Tetromino*
TetrominoManager::get_next_tetronimo()
{
  // Improve the choosing of the tetromino. Not all conditions have been applied
  int choice = mDist(mMersenne);
  if (choice == 1) {
    return Z_block;
  } else if (choice == 2) {
    return L_block;
  } else if (choice == 3) {
    return I_block;
  } else if (choice == 4) {
    return J_block;
  } else {
    return O_block;
  }
}
