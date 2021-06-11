#include "grid.h"

Grid::Grid()
  : mOrigin{ constant::GRID_X0, constant::GRID_Y0 }
{
  for (int idx{ 0 }; idx < constant::N_COLS; ++idx) {
    m_cellGrid[constant::N_ROWS][idx].occupied = true;
  }
}

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
      if (m_cellGrid[idy][idx].occupied) {
        SDL_SetRenderDrawColor(renderer,
                               m_cellGrid[idy][idx].color.red,
                               m_cellGrid[idy][idx].color.green,
                               m_cellGrid[idy][idx].color.blue,
                               m_cellGrid[idy][idx].color.alpha);
        SDL_Rect tmp_Rect = Grid::coord_to_rect(idx, idy);
        SDL_RenderFillRect(renderer, &tmp_Rect);
      }
    }
  }
}

void
Grid::render_lines(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer,
                         colors::WHITE.red,
                         colors::WHITE.green,
                         colors::WHITE.blue,
                         colors::WHITE.alpha);
  int xPos = mOrigin.x;
  int yPos = mOrigin.y;
  for (int idy{ 0 }; idy <= constant::N_ROWS; ++idy) {
    SDL_RenderDrawLine(renderer,
                       xPos,
                       yPos,
                       xPos + constant::N_COLS * constant::CELL_SIZE,
                       yPos);
    yPos += constant::CELL_SIZE;
  }

  xPos = mOrigin.x;
  yPos = mOrigin.y;
  for (int idy{ 0 }; idy <= constant::N_COLS; ++idy) {
    SDL_RenderDrawLine(renderer,
                       xPos,
                       yPos,
                       xPos,
                       yPos + constant::N_ROWS * constant::CELL_SIZE);
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
  auto is_occupied = [](Cell cell) { return cell.occupied == true; };
  int  n_completed_rows = 0;
  int  starting_row = -1;
  bool found = false;
  int  row = constant::N_ROWS - 1;

  while (
    std::any_of(m_cellGrid[row].begin(), m_cellGrid[row].end(), is_occupied) &&
    row > 0) {
    if (std::all_of(
          m_cellGrid[row].begin(), m_cellGrid[row].end(), is_occupied)) {
      n_completed_rows += 1;
      if (!found) {
        found = true;
        starting_row = row;
      }
    }
    row -= 1;
  }

  if (found) {
    for (int completed_row{ starting_row + 1 }; completed_row-- > 0;) {
      for (int col{ 0 }; col < constant::N_COLS; ++col) {
        if (completed_row >= n_completed_rows) {
          m_cellGrid[completed_row][col] =
            m_cellGrid[completed_row - n_completed_rows][col];
        } else {
          m_cellGrid[completed_row][col] = Cell{};
        }
      }
    }
  }
}

Grid::Cell
Grid::get_cell(int idx_x, int idx_y) const
{
  return m_cellGrid[idx_y][idx_x];
}

void
Grid::set_cell(int idx_x, int idx_y, bool occupation, Color color)
{
  m_cellGrid[idx_y][idx_x] = { occupation, color };
}
