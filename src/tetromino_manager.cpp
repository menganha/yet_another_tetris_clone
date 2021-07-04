#include "tetromino_manager.h"
#include "user_interface.h"
#include <SDL2/SDL.h>
#include <ctime>

TetrominoManager::TetrominoManager()
  : mMersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)))
  , cache_{ nullptr }
  , T_block(Tetromino::T_block, colors::LILA)
  , L_block(Tetromino::L_block, colors::WHITE)
  , J_block(Tetromino::J_block, colors::BLUE)
  , Z_block(Tetromino::Z_block, colors::RED)
  , S_block(Tetromino::S_block, colors::GREEN)
  , O_block(Tetromino::O_block, colors::YELLOW)
  , I_block(Tetromino::I_block, colors::CYAN)
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

void
TetrominoManager::RenderCachedTetromino(SDL_Renderer* renderer) const
{
  int rel_pos_x = ui::kNextPiecePosX;
  int rel_pos_y = ui::kNextPiecePosY;

  if (cache_->get_type() == Tetromino::I_block) {
    rel_pos_y -= constant::kCellSize;
  } else if (cache_->get_type() != Tetromino::O_block) {
    rel_pos_x += constant::kCellSize / 2;
  }
  cache_->RenderIntitialStateAt(renderer, rel_pos_x, rel_pos_y);
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
