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
  void render(SDL_Renderer* renderer);
  bool update(const Tetromino* tetronimo);

private:
  struct Cell
  {
    bool occupied{ false };
    int color{ 0 };
  };
  std::array<std::array<Cell, constant::N_HORIZ_CELLS>, constant::N_VERT_CELLS+1> mGrid;
  const SDL_Point mOrigin;
  SDL_Rect coord_to_rect(int idx_x, int idx_y);
  void clear_completed_rows();
  void fill_grid(const Tetromino* tetronimo);
  bool collides_with_tetromino(const Tetromino* tetronimo);
  void render_lines(SDL_Renderer* renderer);
};

#endif /* ifndef GRID_H */
