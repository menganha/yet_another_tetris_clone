#include "grid.h"

Grid::Grid() {}

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
  int x_start = constant::CELL_SIZE;
  int y_start = constant::CELL_SIZE;
  for (int idx{ 0 }; idx <= constant::GRID_HEIGHT; ++idx) {
    SDL_RenderDrawLine(renderer,
                       x_start,
                       y_start,
                       x_start + constant::GRID_WIDTH * constant::CELL_SIZE,
                       y_start);
    y_start += constant::CELL_SIZE;
  }

  x_start = constant::CELL_SIZE;
  y_start = constant::CELL_SIZE;
  for (int idx{ 0 }; idx <= constant::GRID_WIDTH; ++idx) {
    SDL_RenderDrawLine(renderer,
                       x_start,
                       y_start,
                       x_start,
                       y_start + constant::GRID_HEIGHT * constant::CELL_SIZE);
    x_start += constant::CELL_SIZE;
  }
}
