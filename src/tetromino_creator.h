#ifndef TETROMINO_CREATOR_H
#define TETROMINO_CREATOR_H

#include "color.h"
#include "tetromino.h"
#include "tetromino_type.h"

class TetrominoCreator
{
public:
  static Tetromino* create_block(tetrominoType type);
};
#endif /* ifndef TETROMINO_CREATOR_H */
