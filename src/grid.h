#ifndef GRID_H
#define GRID_H

#include "color.h"
#include "constant.h"
#include <SDL2/SDL.h>
#include <array>

class Grid
{

public:
  Grid();

  struct Cell
  {
    bool      occupied{ false };
    SDL_Color color{ colors::BLACK };
  };
  void Render(SDL_Renderer* renderer) const;
  void Update();
  void ClearGrid();
  int  get_completed_rows() const;
  void set_cell(int idx_x, int idx_y, bool occupation, SDL_Color color);
  Cell get_cell(int idx_x, int idx_y) const;

private:
  using CellRow = std::array<Cell, constant::kNCols>;
  using CellGrid = std::array<CellRow, constant::kNRows>;

  CellGrid        cell_grid_;
  SDL_Point const origin_;
  int             completed_rows_;

  int             ClearedRowsToScore(int const cleared_rows);
  void            ClearCompletedRows();
  void            RenderLines(SDL_Renderer* renderer) const;
  void            RenderBlocks(SDL_Renderer* renderer) const;
};

#endif
