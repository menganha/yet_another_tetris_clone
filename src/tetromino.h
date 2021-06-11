#ifndef TETROMINO_H
#define TETROMINO_H

#include "color.h"
#include "constant.h"
#include "grid.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <array>

// Tetrominos are defined with respect to a local frame of reference where the
// point 3,3 is the rotation center
class Tetromino
{
public:
  static const int mSize = 4;
  using ElementCoord = std::array<SDL_Point, mSize>;

  Tetromino(ElementCoord local_coord_list, const Color color);
  void         render(SDL_Renderer* renderer);
  void         reset_position();
  Color        get_color() const;
  ElementCoord get_coord() const;
  void         set_coord(ElementCoord absCoordinates, bool relative = false);
  ElementCoord get_containing_cell_indices() const;
  void         move(int delta_x, int delta_y);
  bool         collides(const Grid& grid) const;
  bool         lands(const Grid& grid) const;
  void         rotate();

private:
  SDL_Point    frameCoord_; // Abs coord of the Tetromino frame of reference
  const Color  color_;
  ElementCoord abs_coord_;  // Abs coord of each tetromino block
  ElementCoord localCoord_; // Rel coord of each tetromino block scaled by
                            // 1/constant::CELL_SIZE
  void         update_abs_coord();
};

#endif
