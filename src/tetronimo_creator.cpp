#include "tetromino_creator.h"

Tetromino*
TetrominoCreator::create_block(tetrominoType type)
{

  switch (type) {
    case tetrominoType::T_block:
      return new Tetromino({ { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, colors::LILA);
    case tetrominoType::L_block:
      return new Tetromino({ { { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, colors::WHITE);
    case tetrominoType::J_block:
      return new Tetromino({ { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, colors::BLUE);
    case tetrominoType::Z_block:
      return new Tetromino({ { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } } }, colors::RED);
    case tetrominoType::S_block:
      return new Tetromino({ { { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } } }, colors::GREEN);
    case tetrominoType::O_block:
      return new Tetromino({ { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } } }, colors::YELLOW);
    case tetrominoType::I_block:
      return new Tetromino({ { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } } }, colors::CYAN);
    default:
      return nullptr;
  }
}
