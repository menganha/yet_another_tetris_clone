#ifndef GRID_H
#define GRID_H

#include "color.h"
#include "constant.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <stdexcept>
#include <array>

class Grid
{

public:
  Grid();
  ~Grid();

  struct Cell
  {
    bool  occupied{ false };
    Color color{ colors::BLACK };
  };
  void render(SDL_Renderer* renderer);
  void update();
  void set_cell(int idx_x, int idx_y, bool occupation, Color color);
  Cell get_cell(int idx_x, int idx_y) const;

private:
  using CellRow = std::array<Cell, constant::N_COLS>;

  std::array<CellRow, constant::N_ROWS> cell_grid_;
  SDL_Point const                       origin_;
  SDL_Rect                              coord_to_rect(int idx_x, int idx_y);

  int  clear_completed_rows(); // Also returns number of completed rows
  void render_lines(SDL_Renderer* renderer);
  void render_blocks(SDL_Renderer* renderer);
};

#endif
