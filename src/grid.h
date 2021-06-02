#ifndef GRID_H
#define GRID_H

#include "color.h"
#include "constant.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <array>

class Grid
{
public:
  struct Cell
  {
    bool  occupied{ false };
    Color color{ colors::WHITE };
  };
  using CellGrid = std::array<std::array<Cell, constant::N_COLS>, constant::N_ROWS + 1>;

  Grid();
  ~Grid();
  void render(SDL_Renderer* renderer);
  void update();
  void set_cell(int idx_x, int idx_y, bool occupation, Color color);
  Cell get_cell(int idx_x, int idx_y) const;

private:
  CellGrid        m_cellGrid;
  const SDL_Point mOrigin;
  SDL_Rect        coord_to_rect(int idx_x, int idx_y);

  void            clear_completed_rows();
  void            render_lines(SDL_Renderer* renderer);
  void            render_blocks(SDL_Renderer* renderer);
};

#endif /* ifndef GRID_H */
