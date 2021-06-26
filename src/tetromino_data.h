#ifndef TETROMINO_DATA_H
#define TETROMINO_DATA_H

#include "constant.h"
#include <SDL2/SDL.h>
#include <array>

// General function/data related to the Tetrominos that do not fit the the higher abstraction of the Tetromino class.

namespace tdata {

  int const kTetrominoSize = 4;

  enum TetrominoType
  {
    T_block,
    L_block,
    J_block,
    Z_block,
    S_block,
    O_block,
    I_block,
    TotalTypes
  };

  // Coordinates of each tetromino piece
  using Coord = std::array<SDL_Point, tdata::kTetrominoSize>;

  // Tetrominos definition with respect to a local frame of reference where the point 3,3 is the rotation center. These
  // coordinates represent the block coordinates of in the initial orientation of the tetromino
  Coord extern const kDefinition[TotalTypes];

  // Renders a tetromino block based on its position and color
  void      RenderBlock(SDL_Renderer* renderer, int const pos_x, int const pos_y, SDL_Color const color);

  // Adjust the relative initial position so that the I block and O block spawn centerd and the rest rounded to the
  // left.

  SDL_Point AdjustedInitialPosition(TetrominoType const type, int pos_x, int pos_y);

  // TODO: define a function that returns the Super Rotation Data, and the initial position of the
  // tetromino in the grid
}

#endif
