#include "grid.h"
#include "tetromino.h"
#include <algorithm>
#include <stdexcept>

Grid::Grid()
  : origin_{ constant::kGridX0, constant::kGridY0 }
  , completed_rows_{ 0 }
{}

void
Grid::Update()
{
  Grid::ClearCompletedRows();
}

void
Grid::Render(SDL_Renderer* renderer) const
{
  Grid::RenderLines(renderer);
  Grid::RenderBlocks(renderer);
}

void
Grid::RenderBlocks(SDL_Renderer* renderer) const
{
  for (int idy{ 0 }; idy < constant::kNRows; ++idy) {
    for (int idx{ 0 }; idx < constant::kNCols; ++idx) {
      if (cell_grid_[idy][idx].occupied) {
        Tetromino::RenderBlock(renderer,
                               idx * constant::kCellSize + constant::kGridX0,
                               idy * constant::kCellSize + constant::kGridY0,
                               cell_grid_[idy][idx].color);
      }
    }
  }
  /* int index = 0; */
  /* for (auto const& row : cell_grid_) { */
  /*   for (auto const& cell : row) { */
  /*     if (cell.occupied) { */
  /*       int x = index % constant::kNCols * constant::kCellSize + constant::kGridX0; */
  /*       int y = index / constant::kNCols * constant::kCellSize + constant::kGridY0; */
  /*       tdata::RenderBlock(renderer, x, y, cell.color); */
  /*     } */
  /*     ++index; */
  /*   } */
  /* } */
}

void
Grid::ClearGrid()
{
  for (auto& row : cell_grid_) {
    Cell empty_cell{ false, colors::BLACK };
    std::fill(row.begin(), row.end(), empty_cell);
  }
}

void
Grid::RenderLines(SDL_Renderer* renderer) const
{
  SDL_SetRenderDrawColor(renderer, colors::WHITE.r, colors::WHITE.g, colors::WHITE.b, 0x20);
  // Render inner horizontal lines
  for (int idx{ 1 }; idx < constant::kNRows; ++idx) {
    int xPos = origin_.x;
    int yPos = origin_.y + constant::kCellSize * idx;
    SDL_RenderDrawLine(renderer, xPos, yPos - 1, xPos + constant::kNCols * constant::kCellSize - 1, yPos - 1);
    SDL_RenderDrawLine(renderer, xPos, yPos, xPos + constant::kNCols * constant::kCellSize - 1, yPos);
    yPos = yPos + constant::kCellSize;
  }

  // Render inner vertical lines
  for (int idx{ 1 }; idx < constant::kNCols; ++idx) {
    int xPos = origin_.x + constant::kCellSize * idx;
    int yPos = origin_.y;
    SDL_RenderDrawLine(renderer, xPos - 1, yPos, xPos - 1, yPos + constant::kNRows * constant::kCellSize - 1);
    SDL_RenderDrawLine(renderer, xPos, yPos, xPos, yPos + constant::kNRows * constant::kCellSize - 1);
    xPos = xPos + constant::kCellSize;
  }

  // Render outer lines
  SDL_SetRenderDrawColor(renderer, colors::WHITE.r, colors::WHITE.g, colors::WHITE.b, colors::WHITE.a);
  for (int idx{ 1 }; idx < 4; ++idx) {
    SDL_Rect rect = { origin_.x - idx,
                      origin_.y - idx,
                      constant::kNCols * constant::kCellSize + 2 * idx,
                      constant::kNRows * constant::kCellSize + 2 * idx };
    SDL_RenderDrawRect(renderer, &rect);
  }
}

void
Grid::ClearCompletedRows()
{
  completed_rows_ = 0;
  auto is_occupied = [](Cell cell) { return cell.occupied == true; };
  int  row = constant::kNRows - 1;
  while (std::any_of(cell_grid_[row].begin(), cell_grid_[row].end(), is_occupied) && row > 0) {

    if (std::all_of(cell_grid_[row].begin(), cell_grid_[row].end(), is_occupied)) {
      ++completed_rows_;
      for (int tmp_row{ row + 1 }; tmp_row-- > 1;) {
        cell_grid_[tmp_row] = cell_grid_[tmp_row - 1];
      }
    } else {
      --row;
    }
  }
}

int
Grid::get_completed_rows() const
{
  return completed_rows_;
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
Grid::set_cell(int idx_x, int idx_y, bool occupation, SDL_Color color)
{
  cell_grid_[idx_y][idx_x] = { occupation, color };
}
