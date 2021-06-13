#include "grid.h"

Grid::Grid()
  : origin_{ constant::GRID_X0, constant::GRID_Y0 }
{}

Grid::~Grid() {}

void
Grid::update()
{
  Grid::clear_completed_rows();
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
  for (int idy{ 0 }; idy < constant::N_ROWS; ++idy) {
    for (int idx{ 0 }; idx < constant::N_COLS; ++idx) {
      if (cell_grid_[idy][idx].occupied) {
        SDL_SetRenderDrawColor(renderer,
                               cell_grid_[idy][idx].color.red,
                               cell_grid_[idy][idx].color.green,
                               cell_grid_[idy][idx].color.blue,
                               cell_grid_[idy][idx].color.alpha);
        SDL_Rect tmp_Rect = Grid::coord_to_rect(idx, idy);
        SDL_RenderFillRect(renderer, &tmp_Rect);
      }
    }
  }
}

void
Grid::render_lines(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, colors::WHITE.red, colors::WHITE.green, colors::WHITE.blue, 0x20);

  // Render inner horizontal lines
  int xPos = origin_.x;
  int yPos = origin_.y;
  for (int idy{ 0 }; idy < constant::N_ROWS; ++idy) {
    SDL_RenderDrawLine(renderer, xPos, yPos - 1, xPos + constant::N_COLS * constant::CELL_SIZE, yPos - 1);
    SDL_RenderDrawLine(renderer, xPos, yPos, xPos + constant::N_COLS * constant::CELL_SIZE, yPos);
    yPos = yPos + constant::CELL_SIZE;
  }

  // Render inner vertical lines
  xPos = origin_.x;
  yPos = origin_.y;
  for (int idy{ 0 }; idy < constant::N_COLS; ++idy) {
    SDL_RenderDrawLine(renderer, xPos - 1, yPos, xPos - 1, yPos + constant::N_ROWS * constant::CELL_SIZE);
    SDL_RenderDrawLine(renderer, xPos, yPos, xPos, yPos + constant::N_ROWS * constant::CELL_SIZE);
    xPos = xPos + constant::CELL_SIZE;
  }

  // Render outter lines
  SDL_SetRenderDrawColor(renderer, colors::WHITE.red, colors::WHITE.green, colors::WHITE.blue, colors::WHITE.alpha);
  xPos = origin_.x;
  yPos = origin_.y;
  SDL_RenderDrawLine(renderer, xPos - 1, yPos - 1, xPos + constant::N_COLS * constant::CELL_SIZE, yPos - 1);
  SDL_RenderDrawLine(renderer, xPos - 1, yPos, xPos + constant::N_COLS * constant::CELL_SIZE, yPos);
  SDL_RenderDrawLine(renderer, xPos - 1, yPos, xPos - 1, yPos + constant::N_ROWS * constant::CELL_SIZE);
  SDL_RenderDrawLine(renderer, xPos, yPos, xPos, yPos + constant::N_ROWS * constant::CELL_SIZE);
  xPos = origin_.x + constant::N_COLS * constant::CELL_SIZE;
  yPos = origin_.y;
  SDL_RenderDrawLine(renderer, xPos - 1, yPos, xPos - 1, yPos + constant::N_ROWS * constant::CELL_SIZE);
  SDL_RenderDrawLine(renderer, xPos, yPos, xPos, yPos + constant::N_ROWS * constant::CELL_SIZE);
  xPos = origin_.x;
  yPos = origin_.y + constant::N_ROWS * constant::CELL_SIZE;
  SDL_RenderDrawLine(renderer, xPos, yPos - 1, xPos + constant::N_COLS * constant::CELL_SIZE, yPos - 1);
  SDL_RenderDrawLine(renderer, xPos, yPos, xPos + constant::N_COLS * constant::CELL_SIZE, yPos);
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

int
Grid::clear_completed_rows()
{
  auto is_occupied = [](Cell cell) { return cell.occupied == true; };
  int  n_completed_rows = 0;
  int  row = constant::N_ROWS - 1;
  while (std::any_of(cell_grid_[row].begin(), cell_grid_[row].end(), is_occupied) && row > 0) {

    if (std::all_of(cell_grid_[row].begin(), cell_grid_[row].end(), is_occupied)) {
      ++n_completed_rows;
      for (int tmp_row{ row + 1 }; tmp_row-- > 1;) {
        cell_grid_[tmp_row] = cell_grid_[tmp_row - 1];
      }
    } else {
      --row;
    }
  }
  return n_completed_rows;
}

Grid::Cell
Grid::get_cell(int idx_x, int idx_y) const
{
  if (idx_y >= constant::N_ROWS || idx_x >= constant::N_COLS) {
    throw std::out_of_range(" Index value is out of range");
  }
  return cell_grid_[idx_y][idx_x];
}

void
Grid::set_cell(int idx_x, int idx_y, bool occupation, Color color)
{
  cell_grid_[idx_y][idx_x] = { occupation, color };
}
