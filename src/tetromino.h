#ifndef TETROMINO_H
#define TETROMINO_H

#include "color.h"
#include "constant.h"
#include "grid.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <array>

// TODO: Big change: include the static tetromino-shape data since there will be no other type of tetromino more than
// the 4 main ones. plus we need to keep the original orientation for when we reset the tetromino The constructor should
// now accepts just the type. Color and shape is handled within the class

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
    Total
  };

  // Coordinates of each tetromino piece
  using Coord = std::array<SDL_Point, tdata::kTetrominoSize>;

  // Tetrominos definition with respect to a local frame of reference where the point 3,3 is the rotation center. These
  // coordinates represent the block coordinates of in the initial orientation of the tetromino
  Coord const kDefinition[Total] = { { { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } },   // T block
                                     { { { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } },   // L block
                                     { { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } },   // J block
                                     { { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } } },   // Z block
                                     { { { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } } },   // S block
                                     { { { 1, 0 }, { 2, 0 }, { 1, 1 }, { 2, 1 } } },   // I block
                                     { { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } } } }; // O block

  // TODO: define a function that returns the Super Rotation Data, and the initial position of the
  // tetromino in the grid
}

class Tetromino
{

public:
  // TODO: Constructor should also include initial position and cell size
  Tetromino(tdata::TetrominoType type, const Color color);

  void         Render(SDL_Renderer* renderer) const;
  void         RenderIntitialStateAt(SDL_Renderer* renderer, int pos_x, int pos_y) const;
  void         ResetPosition();
  Color        GetColor() const;
  tdata::Coord get_containing_cell_indices() const;
  void         Move(int delta_x, int delta_y);
  bool         Collides(const Grid& grid) const;
  bool         Lands(const Grid& grid) const;
  void         Rotate();
  void         CacheCoordinates();
  void         RestoreFromCache();

private:
  Color const                color_;
  tdata::TetrominoType const tetromino_type_;
  SDL_Point const            initial_frame_coord_;
  SDL_Point                  frame_coord_;
  SDL_Point                  cache_frame_coord_;
  tdata::Coord const         initial_rel_coord_;
  tdata::Coord               rel_coord_;
  tdata::Coord               cache_rel_coord_;
  tdata::Coord               abs_coord_;
  void                       UpdateAbsCoord();
};

#endif
