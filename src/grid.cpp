#include "grid.h"

Grid::Grid()
  : mOrigin{ constant::GRID_X0, constant::GRID_Y0 }
{
  for (int idx{ 0 }; idx < constant::N_HORIZ_CELLS; ++idx) {
    mGrid[constant::N_VERT_CELLS][idx].occupied = true;
  }
}

bool
Grid::update(const Tetromino* tetromino)
{
  bool has_landed{ false };
  if (Grid::collides_with_tetromino(tetromino)) {
    Grid::fill_grid(tetromino);
    has_landed = true;
  }
  Grid::clear_completed_rows();
  return has_landed;
}

bool
Grid::collides_with_tetromino(const Tetromino* tetromino)
{
  Tetromino::tetrominoRectCoord_t tetrominoCoord = tetromino->get_coord();

  for (int idx{ constant::N_VERT_CELLS + 1 }; idx-- > 0;) {
    for (int idy{ 0 }; idy < constant::N_HORIZ_CELLS; ++idy) {
      if (!mGrid[idx][idy].occupied) {
        continue;
      }
      SDL_Rect tmp_rect{ idy * constant::CELL_SIZE + constant::GRID_X0,
                         idx * constant::CELL_SIZE + constant::GRID_Y0,
                         constant::CELL_SIZE,
                         constant::CELL_SIZE };
      for (auto rect : tetrominoCoord) {
        if (SDL_HasIntersection(&rect, &tmp_rect)) {
          return true;
        }
      }
    }
  }
  return false;
}

void
Grid::fill_grid(const Tetromino* tetromino)
{
  Color color = tetromino->get_color();
  for (auto indices : tetromino->get_containing_cell_indices()) {
    mGrid[indices.y][indices.x] = {true, color};
  }
}

void
Grid::render(SDL_Renderer* renderer)
{
  Grid::render_lines(renderer);
  Grid::render_blocks(renderer);
}

void
Grid::render_blocks(SDL_Renderer* renderer)
{
  for (int idy{ 0 }; idy < constant::N_VERT_CELLS; ++idy) {
    for (int idx{ 0 }; idx < constant::N_HORIZ_CELLS; ++idx) {
      if (mGrid[idy][idx].occupied) {
        SDL_SetRenderDrawColor(renderer,
                               mGrid[idy][idx].color.red,
                               mGrid[idy][idx].color.green,
                               mGrid[idy][idx].color.blue,
                               mGrid[idy][idx].color.alpha);
        SDL_Rect tmp_Rect = Grid::coord_to_rect(idx, idy);
        SDL_RenderFillRect(renderer, &tmp_Rect);
      }
    }
  }
}

void
Grid::render_lines(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(
    renderer, colors::WHITE.red, colors::WHITE.green, colors::WHITE.blue, colors::WHITE.alpha);
  int xPos = mOrigin.x;
  int yPos = mOrigin.y;
  for (int idy{ 0 }; idy <= constant::N_VERT_CELLS; ++idy) {
    SDL_RenderDrawLine(renderer, xPos, yPos, xPos + constant::N_HORIZ_CELLS * constant::CELL_SIZE, yPos);
    yPos += constant::CELL_SIZE;
  }

  xPos = mOrigin.x;
  yPos = mOrigin.y;
  for (int idy{ 0 }; idy <= constant::N_HORIZ_CELLS; ++idy) {
    SDL_RenderDrawLine(renderer, xPos, yPos, xPos, yPos + constant::N_VERT_CELLS * constant::CELL_SIZE);
    xPos += constant::CELL_SIZE;
  }
}

SDL_Rect
Grid::coord_to_rect(int ind_x, int ind_y)
{
  SDL_Rect rect{ ind_x * constant::CELL_SIZE + constant::GRID_X0,
                 ind_y * constant::CELL_SIZE + constant::GRID_Y0,
                 constant::CELL_SIZE,
                 constant::CELL_SIZE };
  return rect;
}

void
Grid::clear_completed_rows()
{
  for (int idx{ constant::N_VERT_CELLS }; idx-- > 0;) {
    if (std::all_of(mGrid[idx].begin(), mGrid[idx].end(), [](Cell cell) { return cell.occupied == true; })) {
      for (int idy{ 0 }; idy < constant::N_HORIZ_CELLS; ++idy) {
        mGrid[idx][idy].occupied = false;
      }
    }
  }
}
