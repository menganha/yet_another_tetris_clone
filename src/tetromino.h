#ifndef TETROMINO_H
#define TETROMINO_H

#include "color.h"
#include "constant.h"
#include "grid.h"
#include "tetromino_data.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <array>

class Tetromino
{

public:
  // TODO: Constructor should also include initial position and cell size
  Tetromino(tdata::TetrominoType type, const SDL_Color color);

  void                 Render(SDL_Renderer* renderer) const;
  void                 RenderIntitialStateAt(SDL_Renderer* renderer, int const pos_x, int const pos_y) const;
  void                 ResetPosition();
  SDL_Color            GetColor() const;
  tdata::Coord         get_containing_cell_indices() const;
  tdata::TetrominoType Type() const;
  void                 Move(int delta_x, int delta_y);
  bool                 Collides(const Grid& grid) const;
  bool                 Lands(const Grid& grid) const;
  void                 Rotate();
  void                 CacheCoordinates();
  void                 RestoreFromCache();

private:
  SDL_Color const            color_;
  tdata::TetrominoType const type_;
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
