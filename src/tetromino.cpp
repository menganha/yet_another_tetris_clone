#include "tetromino.h"

Tetromino::Tetromino(tdata::TetrominoType tetromino_type, const Color color)
  : color_{ color }
  , tetromino_type_{ tetromino_type }
  , initial_frame_coord_{ 4 * constant::kCellSize + constant::kGridX0, constant::kGridY0 }
  , initial_rel_coord_{ tdata::kDefinition[tetromino_type] }
{
  ResetPosition();
}

void
Tetromino::ResetPosition()
{
  frame_coord_ = initial_frame_coord_;
  rel_coord_ = initial_rel_coord_;
  UpdateAbsCoord();
  CacheCoordinates();
}

void
Tetromino::Render(SDL_Renderer* renderer) const
{
  SDL_SetRenderDrawColor(renderer, color_.red, color_.green, color_.blue, color_.alpha);
  for (auto abs_coord : abs_coord_) {
    SDL_Rect rect{ abs_coord.x, abs_coord.y, constant::kCellSize, constant::kCellSize };
    SDL_RenderFillRect(renderer, &rect);
  }
}

void
Tetromino::RenderIntitialStateAt(SDL_Renderer* renderer, int pos_x, int pos_y) const
{
  SDL_SetRenderDrawColor(renderer, color_.red, color_.green, color_.blue, color_.alpha);
  for (auto rel_coord : initial_rel_coord_) {
    SDL_Rect rect{ pos_x + rel_coord.x * constant::kCellSize,
                   pos_y + rel_coord.y * constant::kCellSize,
                   constant::kCellSize,
                   constant::kCellSize };
    SDL_RenderFillRect(renderer, &rect);
  }
}

void
Tetromino::Move(int delta_x, int delta_y)
{
  frame_coord_ = { frame_coord_.x + delta_x, frame_coord_.y + delta_y };
  UpdateAbsCoord();
}

void
Tetromino::Rotate()
{
  for (std::size_t idx = 0; idx < rel_coord_.size(); ++idx) {
    int tmp_x = -rel_coord_[idx].y + 2; // (x-x0) cos t - (y-y0) sin t
    int tmp_y = rel_coord_[idx].x;      // (x-x0) sin t + (y-y0) cos t
    rel_coord_[idx] = { tmp_x, tmp_y };
  }
  UpdateAbsCoord();
}

bool
Tetromino::Collides(const Grid& grid) const
{
  // Lambda to checks collision with the grid borders
  auto out_of_bounds = [](SDL_Point coord) {
    return (coord.x < constant::kGridX0) || (coord.x > constant::kGridX1 - constant::kCellSize) ||
           (coord.y > constant::kGridY1 - constant::kCellSize);
  };

  if (std::any_of(abs_coord_.begin(), abs_coord_.end(), out_of_bounds)) {
    return true;
  }

  // Checks if collides with others blocks
  for (SDL_Point indices : get_containing_cell_indices()) {
    if (grid.get_cell(indices.x, indices.y).occupied) {
      return true;
    }
  }

  return false;
}

bool
Tetromino::Lands(const Grid& grid) const
{
  for (SDL_Point indices : get_containing_cell_indices()) {
    if (indices.y == constant::kNRows - 1) { // If it is the last row
      return true;
    } else if (grid.get_cell(indices.x, indices.y + 1).occupied) {
      return true;
    }
  }
  return false;
}

tdata::Coord
Tetromino::get_containing_cell_indices() const
{
  // Gets the closest cell indices of the grid that contain the tetromino. If
  // tetromino is between two vertical cells it only retruns the one up
  tdata::Coord cell_indices;

  for (std::size_t idx = 0; idx < abs_coord_.size(); ++idx) {
    cell_indices[idx] = { (abs_coord_[idx].x - constant::kGridX0) / constant::kCellSize,
                          (abs_coord_[idx].y - constant::kGridY0) / constant::kCellSize };
  }
  return cell_indices;
}

Color
Tetromino::GetColor() const
{
  return color_;
}

void
Tetromino::UpdateAbsCoord()
{
  // Updates the absolute coordinates if either the frame or the relative coordinates change
  for (std::size_t idx = 0; idx < abs_coord_.size(); ++idx) {
    abs_coord_[idx] = { rel_coord_[idx].x * constant::kCellSize + frame_coord_.x,
                        rel_coord_[idx].y * constant::kCellSize + frame_coord_.y };
  }
}

void
Tetromino::CacheCoordinates()
{
  cache_frame_coord_ = frame_coord_;
  cache_rel_coord_ = rel_coord_;
}

void
Tetromino::RestoreFromCache()
{
  frame_coord_ = cache_frame_coord_;
  rel_coord_ = cache_rel_coord_;
  UpdateAbsCoord();
}
