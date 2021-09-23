#include "tetromino.h"
#include "color.h"
#include "constant.h"
#include "grid.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

Tetromino::Tetromino(Type tetromino_type, const SDL_Color color)
  : color_{ color }
  , type_{ tetromino_type }
  , initial_frame_coord_{ AdjustedInitialPosition(3 * constant::kCellSize + constant::kGridX0, constant::kGridY0) }
  , initial_rel_coord_{ kDefinition[tetromino_type] }
  , rotation_index_{ rot_0 }
  , offset_possibilities_{ tetromino_type == O_block ? offset_possibilities_O_Tetromino
                                                     : offset_possibilities_Tetromino }
{
  ResetPosition();
}

void
Tetromino::ResetPosition()
{
  frame_coord_ = initial_frame_coord_;
  rel_coord_ = initial_rel_coord_;
  rotation_index_ = rot_0;
  UpdateAbsCoord();
  CacheCoordinates();
}

void
Tetromino::Render(SDL_Renderer* renderer) const
{
  for (auto abs_coord : abs_coord_) {
    RenderBlock(renderer, abs_coord.x, abs_coord.y, color_);
  }
}

void
Tetromino::RenderIntitialStateAt(SDL_Renderer* renderer, int const pos_x, int const pos_y) const
{
  SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
  for (auto rel_coord : initial_rel_coord_) {
    RenderBlock(renderer, pos_x + rel_coord.x * constant::kCellSize, pos_y + rel_coord.y * constant::kCellSize, color_);
  }
}

void
Tetromino::RenderBlock(SDL_Renderer* renderer, int const pos_x, int const pos_y, SDL_Color color)
{
  /*
     Renders a tetromino block based on its position and color
  */
  SDL_Rect rect{ pos_x, pos_y, constant::kCellSize, constant::kCellSize };
  // inside
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &rect);
  // outline
  SDL_SetRenderDrawColor(renderer, color.r * 0.7, color.g * 0.7, color.b * 0.7, color.a);
  SDL_RenderDrawRect(renderer, &rect);
}

void
Tetromino::Move(int delta_x, int delta_y)
{
  frame_coord_ = { frame_coord_.x + delta_x, frame_coord_.y + delta_y };
  UpdateAbsCoord();
}

void
Tetromino::Rotate(bool direction, int offset_case)
{
  /*
     Rotates the piece using the input offset case for added translation in case piece is hitting a wall
  */

  // direction == true means counter-clockwise else clockwise
  // x_new = (x-x0) cos t - (y-y0) sin t + x0
  // y_new = (x-x0) sin t + (y-y0) cos t + y0
  int previous_rotation_state = GetRotationState(rotation_index_);
  if (direction) {
    rotation_index_ += 1;
    for (std::size_t idx = 0; idx < rel_coord_.size(); ++idx) {
      rel_coord_[idx] = { -rel_coord_[idx].y + 2, rel_coord_[idx].x };
    }
  } else {
    rotation_index_ -= 1;
    for (std::size_t idx = 0; idx < rel_coord_.size(); ++idx) {
      rel_coord_[idx] = { rel_coord_[idx].y, -rel_coord_[idx].x + 2 };
    }
  }
  // More than thre rotations get you back to the regular state
  if (abs(rotation_index_) > 3) {
    rotation_index_ = 0;
  }
  int       rotation_state = GetRotationState(rotation_index_);
  SDL_Point offset_curr_state;
  SDL_Point offset_prev_state;

  if (type_ == I_block) {
    offset_curr_state = I_Tetromino_OffSetData[offset_case][rotation_state];
    offset_prev_state = I_Tetromino_OffSetData[offset_case][previous_rotation_state];
  } else if (type_ == O_block) {
    offset_curr_state = O_Tetromino_OffSetData[offset_case][rotation_state];
    offset_prev_state = O_Tetromino_OffSetData[offset_case][previous_rotation_state];
  } else {
    offset_curr_state = OffSetData[offset_case][rotation_state];
    offset_prev_state = OffSetData[offset_case][previous_rotation_state];
  }

  int x_offset = offset_prev_state.x - offset_curr_state.x;
  int y_offset = offset_prev_state.y - offset_curr_state.y;
  frame_coord_ = { frame_coord_.x + x_offset * constant::kCellSize, frame_coord_.y - y_offset * constant::kCellSize };

  UpdateAbsCoord();
}

int
Tetromino::GetRotationState(int rotation_index)
{
  switch (rotation_index) {
    case 0:
      return rot_0;
    case 1:
      return rot_R;
    case 2:
      return rot_2;
    case 3:
      return rot_L;
    case -1:
      return rot_L;
    case -2:
      return rot_2;
    case -3:
      return rot_R;
    default:
      throw std::invalid_argument("Not a valid rotation index");
  }
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
  /*
     Checks if the Tetromino is directly above anothe piece of the grid
  */
  for (SDL_Point indices : get_containing_cell_indices()) {
    if (indices.y == constant::kNRows - 1) { // If it is the last row
      return true;
    } else if (grid.get_cell(indices.x, indices.y + 1).occupied) {
      return true;
    }
  }
  return false;
}

Tetromino::Type
Tetromino::get_type() const
{
  return type_;
}

int
Tetromino::get_offset_possibilities() const
{
  return offset_possibilities_;
}

Tetromino::Coord
Tetromino::get_containing_cell_indices() const
{
  // Gets the closest cell indices of the grid that contain the tetromino. If
  // tetromino is between two vertical cells it only retruns the one up
  Coord cell_indices;

  for (std::size_t idx = 0; idx < abs_coord_.size(); ++idx) {
    cell_indices[idx] = { (abs_coord_[idx].x - constant::kGridX0) / constant::kCellSize,
                          (abs_coord_[idx].y - constant::kGridY0) / constant::kCellSize };
  }
  return cell_indices;
}

SDL_Color
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
  cache_rotation_index_ = rotation_index_;
}

void
Tetromino::RestoreFromCache()
{
  frame_coord_ = cache_frame_coord_;
  rel_coord_ = cache_rel_coord_;
  rotation_index_ = cache_rotation_index_;
  UpdateAbsCoord();
}

Tetromino::Coord const Tetromino::kDefinition[Tetromino::TotalTypes] = {
  { { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, // T block
  { { { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, // L block
  { { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, // J block
  { { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } } }, // Z block
  { { { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } } }, // S block
  { { { 1, 0 }, { 2, 0 }, { 1, 1 }, { 2, 1 } } }, // O block
  { { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } } }  // I block
};

std::array<SDL_Point, Tetromino::TotalRotationTypes> const
  Tetromino::OffSetData[Tetromino::offset_possibilities_Tetromino] = {
    { { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } } },    // Offset 1
    { { { 0, 0 }, { 1, 0 }, { 0, 0 }, { -1, 0 } } },   // Offset 2
    { { { 0, 0 }, { 1, -1 }, { 0, 0 }, { -1, -1 } } }, // Offset 3
    { { { 0, 0 }, { 0, 2 }, { 0, 0 }, { 0, 2 } } },    // Offset 4
    { { { 0, 0 }, { 1, 2 }, { 0, 0 }, { -1, 2 } } },   // Offset 5
  };

std::array<SDL_Point, Tetromino::TotalRotationTypes> const
  Tetromino::I_Tetromino_OffSetData[Tetromino::offset_possibilities_Tetromino] = {
    { { { 0, 0 }, { -1, 0 }, { -1, 1 }, { 0, 1 } } }, // Offset 1
    { { { -1, 0 }, { 0, 0 }, { 1, 1 }, { 0, 1 } } },  // Offset 2
    { { { 2, 0 }, { 0, 0 }, { -2, 1 }, { 0, 1 } } },  // Offset 3
    { { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } } }, // Offset 4
    { { { 2, 0 }, { 0, -2 }, { -2, 0 }, { 0, 2 } } }, // Offset 5
  };

std::array<SDL_Point, Tetromino::TotalRotationTypes> const
  Tetromino::O_Tetromino_OffSetData[Tetromino::offset_possibilities_O_Tetromino] = {
    { { { 0, 0 }, { 0, -1 }, { -1, -1 }, { -1, 0 } } }, // Offset 1
  };

SDL_Point
Tetromino::AdjustedInitialPosition(int pos_x, int pos_y)
{
  // Adjust so that the I block goes one block up
  if (type_ == I_block) {
    pos_y -= constant::kCellSize;
  }
  return { pos_x, pos_y };
}
