#include "grid.h"

Grid::Grid()
  : mOrigin{ constant::GRID_X0, constant::GRID_Y0 }
{}

void
Grid::render(SDL_Renderer* renderer)
{
  Grid::render_lines(renderer);
}

void
Grid::render_lines(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer,
                         constant::WHITE.red,
                         constant::WHITE.green,
                         constant::WHITE.blue,
                         constant::WHITE.alpha);
  int x_start = mOrigin.x;
  int y_start = mOrigin.y;
  for (int idx{ 0 }; idx <= constant::N_VERT_CELLS; ++idx) {
    SDL_RenderDrawLine(
      renderer, x_start, y_start, x_start + constant::N_HORIZ_CELLS * constant::CELL_SIZE, y_start);
    y_start += constant::CELL_SIZE;
  }

  x_start = mOrigin.x;
  y_start = mOrigin.y;
  for (int idx{ 0 }; idx <= constant::N_HORIZ_CELLS; ++idx) {
    SDL_RenderDrawLine(
      renderer, x_start, y_start, x_start, y_start + constant::N_VERT_CELLS * constant::CELL_SIZE);
    x_start += constant::CELL_SIZE;
  }
}
