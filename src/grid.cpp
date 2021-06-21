#include "grid.h"

Grid::Grid()
  : origin_{ constant::kGridX0, constant::kGridY0 }
{}

void
Grid::Update()
{
  Grid::clear_completed_rows();
}

void
Grid::Render(SDL_Renderer* renderer) const
{
  Grid::render_lines(renderer);
  Grid::render_blocks(renderer);
}

void
Grid::render_blocks(SDL_Renderer* renderer) const
{
  for (int idy{ 0 }; idy < constant::kNRows; ++idy) {
    for (int idx{ 0 }; idx < constant::kNCols; ++idx) {
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
Grid::render_lines(SDL_Renderer* renderer) const
{
  SDL_SetRenderDrawColor(renderer, colors::WHITE.red, colors::WHITE.green, colors::WHITE.blue, 0x20);

  // Render inner horizontal lines
  int xPos = origin_.x;
  int yPos = origin_.y;
  for (int idy{ 0 }; idy < constant::kNRows; ++idy) {
    SDL_RenderDrawLine(renderer, xPos, yPos - 1, xPos + constant::kNCols * constant::kCellSize, yPos - 1);
    SDL_RenderDrawLine(renderer, xPos, yPos, xPos + constant::kNCols * constant::kCellSize, yPos);
    yPos = yPos + constant::kCellSize;
  }

  // Render inner vertical lines
  xPos = origin_.x;
  yPos = origin_.y;
  for (int idy{ 0 }; idy < constant::kNCols; ++idy) {
    SDL_RenderDrawLine(renderer, xPos - 1, yPos, xPos - 1, yPos + constant::kNRows * constant::kCellSize);
    SDL_RenderDrawLine(renderer, xPos, yPos, xPos, yPos + constant::kNRows * constant::kCellSize);
    xPos = xPos + constant::kCellSize;
  }

  // Render outter lines
  SDL_SetRenderDrawColor(renderer, colors::WHITE.red, colors::WHITE.green, colors::WHITE.blue, colors::WHITE.alpha);
  xPos = origin_.x;
  yPos = origin_.y;
  SDL_RenderDrawLine(renderer, xPos - 1, yPos - 1, xPos + constant::kNCols * constant::kCellSize, yPos - 1);
  SDL_RenderDrawLine(renderer, xPos - 1, yPos, xPos + constant::kNCols * constant::kCellSize, yPos);
  SDL_RenderDrawLine(renderer, xPos - 1, yPos, xPos - 1, yPos + constant::kNRows * constant::kCellSize);
  SDL_RenderDrawLine(renderer, xPos, yPos, xPos, yPos + constant::kNRows * constant::kCellSize);
  xPos = origin_.x + constant::kNCols * constant::kCellSize;
  yPos = origin_.y;
  SDL_RenderDrawLine(renderer, xPos - 1, yPos, xPos - 1, yPos + constant::kNRows * constant::kCellSize);
  SDL_RenderDrawLine(renderer, xPos, yPos, xPos, yPos + constant::kNRows * constant::kCellSize);
  xPos = origin_.x;
  yPos = origin_.y + constant::kNRows * constant::kCellSize;
  SDL_RenderDrawLine(renderer, xPos, yPos - 1, xPos + constant::kNCols * constant::kCellSize, yPos - 1);
  SDL_RenderDrawLine(renderer, xPos, yPos, xPos + constant::kNCols * constant::kCellSize, yPos);
}

SDL_Rect
Grid::coord_to_rect(int ind_x, int ind_y) const
{
  SDL_Rect rect{ ind_x * constant::kCellSize + constant::kGridX0,
                 ind_y * constant::kCellSize + constant::kGridY0,
                 constant::kCellSize,
                 constant::kCellSize };
  return rect;
}

int
Grid::clear_completed_rows()
{
  auto is_occupied = [](Cell cell) { return cell.occupied == true; };
  int  n_completed_rows = 0;
  int  row = constant::kNRows - 1;
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
  if (idx_y >= constant::kNRows || idx_x >= constant::kNCols) {
    throw std::out_of_range(" Index value is out of range");
  }
  return cell_grid_[idx_y][idx_x];
}

void
Grid::set_cell(int idx_x, int idx_y, bool occupation, Color color)
{
  cell_grid_[idx_y][idx_x] = { occupation, color };
}
