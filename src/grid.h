#ifndef GRID_H
#define GRID_H

#include "color.h"
#include "constant.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <array>
#include <stdexcept>

class Grid
{

public:
  Grid();

  struct Cell
  {
    bool  occupied{ false };
    Color color{ colors::BLACK };
  };
  void Render(SDL_Renderer* renderer) const;
  void Update();
  void set_cell(int idx_x, int idx_y, bool occupation, Color color);
  Cell get_cell(int idx_x, int idx_y) const;

private:
  using CellRow = std::array<Cell, constant::kNCols>;
  using CellGrid = std::array<CellRow, constant::kNRows>;

  CellGrid        cell_grid_;
  SDL_Point const origin_;
  SDL_Rect        coord_to_rect(int idx_x, int idx_y) const;

  int             ClearCompletedRows(); // Also returns number of completed rows
  void            RenderLines(SDL_Renderer* renderer) const;
  void            RenderBlocks(SDL_Renderer* renderer) const;
};

#endif
