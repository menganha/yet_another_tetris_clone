#ifndef TETROMINO_H
#define TETROMINO_H

#include "color.h"
#include "constant.h"
#include "controller.h"
#include "grid.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <array>

class Tetromino
{
  // Tetrominos are defined with respect to a local frame of reference where the point 3,3 is the
  // rotation center

public:
  static const int mSize = 4;
  using ElementCoord_t = std::array<SDL_Point, mSize>;

  Tetromino(ElementCoord_t local_coord_list, const Color color);
  ~Tetromino();

  void           render(SDL_Renderer* renderer);
  void           update(const Controller& controller, Grid& grid);
  bool           has_landed() const;
  void           set_gravity(const int gravity);
  void           reset_position();
  Color          get_color() const;
  ElementCoord_t get_coord() const;
  ElementCoord_t get_containing_cell_indices(const ElementCoord_t absCoord) const;

private:
  int            mGravity; // Should always be a positive integer
  bool           mHasLanded;
  SDL_Point      mFrameCoord; // Absolute coordinate of the Tetromino frame of reference
  const Color    mColor;
  ElementCoord_t mAbsCoord;   // Absolute coordinates of each tetromino
  ElementCoord_t mLocalCoord; // Scaled local coordinates of each tetromino by the
                              // factor 1/constant::CELL_SIZE

  ElementCoord_t get_abs_coordinates(const SDL_Point      frameCoord,
                                     const ElementCoord_t localCoord) const;
  bool           has_collided(const ElementCoord_t absCoord, const Grid& grid) const;
  bool           overlaps_blocks(const ElementCoord_t absCoord,
                                 const Grid&          grid,
                                 const bool           below = false) const;
  void           fall(Grid& grid);
  void           move(const Controller& controller, const Grid& grid);
  void           rotate(const Grid& grid);
};

#endif
