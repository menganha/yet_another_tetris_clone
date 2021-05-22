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
  std::array<std::array<Cell, constant::GRID_WIDTH>, constant::GRID_HEIGHT>
    mGrid;

  void clear_row();
  void render_lines(SDL_Renderer* renderer);
};

#endif /* ifndef GRID_H */
