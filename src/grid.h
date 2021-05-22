#ifndef GRID_H
#define GRID_H

#include "constant.h"
#include "tetromino.h"
#include <SDL2/SDL.h>
#include <array>

class Grid
{
public:
  Grid();
  ~Grid();
  /* void update(const Tetromino* tTetronimo); */
  void render(SDL_Renderer* renderer);

private:
  struct Cell
  {
    bool occupied{ false };
    int color{ 0 };
  };
  std::array<std::array<Cell, constant::N_HORIZ_CELLS>, constant::N_VERT_CELLS>
    mGrid;

  const SDL_Point mOrigin;
  void clear_row();
  void render_lines(SDL_Renderer* renderer);
};

#endif /* ifndef GRID_H */
