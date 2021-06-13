#include "tetromino.h"

Tetromino::Tetromino(ElementCoord coordList, const Color color)
  : color_{ color }
  , localCoord_{ coordList }
{
  reset_position();
}

void
Tetromino::render(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, color_.red, color_.green, color_.blue, color_.alpha);
  for (int idx = 0; idx < mSize; idx++) {
    SDL_Rect rect{ abs_coord_[idx].x, abs_coord_[idx].y, constant::CELL_SIZE, constant::CELL_SIZE };
    SDL_RenderFillRect(renderer, &rect);
  }
}

void
Tetromino::reset_position()
{
  frameCoord_ = { 4 * constant::CELL_SIZE + constant::GRID_X0, constant::GRID_Y0 };
  update_abs_coord();
}

void
Tetromino::rotate()
{
  for (int idx = 0; idx < mSize; idx++) {
    int tmp_x;
    int tmp_y;
    tmp_x = -localCoord_[idx].y + 2; // (x-x0) cos t - (y-y0) sin t
    tmp_y = localCoord_[idx].x;      // (x-x0) sin t + (y-y0) cos t
    localCoord_[idx] = { tmp_x, tmp_y };
  }
  update_abs_coord();
}

void
Tetromino::move(int delta_x, int delta_y)
{
  frameCoord_ = { frameCoord_.x + delta_x, frameCoord_.y + delta_y };
  update_abs_coord();
}

bool
Tetromino::collides(const Grid& grid) const
{
  // Checks for the collission with the grid borders
  auto out_of_bounds = [](SDL_Point coord) {
    return (coord.x < constant::GRID_X0) || 
           (coord.x > constant::GRID_X1 - constant::CELL_SIZE) ||
           (coord.y > constant::GRID_Y1 - constant::CELL_SIZE);
  };

  if (std::any_of(abs_coord_.begin(), abs_coord_.end(), out_of_bounds)) {
    return true;
  }

  // Checks if colides with others blocks
  for (SDL_Point indices : get_containing_cell_indices()) {
    if (grid.get_cell(indices.x, indices.y).occupied) {
      return true;
    }
  }
  
  return false;
}

bool
Tetromino::lands(const Grid& grid) const
{
  for (SDL_Point indices : get_containing_cell_indices()) {
    if (indices.y == constant::N_ROWS - 1) { // If it is the last row
      return true;
    } else if (grid.get_cell(indices.x, indices.y + 1).occupied) {
      return true;
    }
  }
  return false;
}

Tetromino::ElementCoord
Tetromino::get_containing_cell_indices() const
{
  // Gets the closest cell indices of the grid that contain the tetromino. If
  // tetromino is between two vertical cells it only retruns the one up
  ElementCoord cell_indices;

  for (int idx = 0; idx < mSize; ++idx) {
    cell_indices[idx] = { (abs_coord_[idx].x - constant::GRID_X0) / constant::CELL_SIZE,
                          (abs_coord_[idx].y - constant::GRID_Y0) / constant::CELL_SIZE };
  }
  return cell_indices;
}

Tetromino::ElementCoord
Tetromino::get_coord() const
{
  return abs_coord_;
}

void
Tetromino::set_coord(Tetromino::ElementCoord absCoordinates, bool relative)
{
  // Depending on the tipe of transformation it will update only the relative or
  // only the coordinates of the frame of reference
  abs_coord_ = absCoordinates;
  if (relative) {
    for (int idx = 0; idx < mSize; idx++) {
      localCoord_[idx].x = (abs_coord_[idx].x - frameCoord_.x) / constant::CELL_SIZE;
      localCoord_[idx].y = (abs_coord_[idx].y - frameCoord_.y) / constant::CELL_SIZE;
    }
  } else {
    frameCoord_.x = abs_coord_[0].x - localCoord_[0].x * constant::CELL_SIZE;
    frameCoord_.y = abs_coord_[0].y - localCoord_[0].y * constant::CELL_SIZE;
  }
}

Color
Tetromino::get_color() const
{
  return color_;
}

void
Tetromino::update_abs_coord()
{
  // Updates the absolute coordinates if either the frame or the relative
  // coordinates change
  for (int idx = 0; idx < mSize; idx++) {
    abs_coord_[idx] = { localCoord_[idx].x * constant::CELL_SIZE + frameCoord_.x,
                        localCoord_[idx].y * constant::CELL_SIZE + frameCoord_.y };
  }
}
