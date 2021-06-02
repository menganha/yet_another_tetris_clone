#include "tetromino.h"

Tetromino::Tetromino(ElementCoord_t coordList, const Color color)
  : mGravity{ 2 }
  , mHasLanded{ false }
  , mColor{ color }
  , mLocalCoord{ coordList }
{
  reset_position();
}

Tetromino::~Tetromino() {}

void
Tetromino::render(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, mColor.red, mColor.green, mColor.blue, mColor.alpha);
  for (int idx = 0; idx < mSize; idx++) {
    SDL_Rect rect{ mAbsCoord[idx].x, mAbsCoord[idx].y, constant::CELL_SIZE, constant::CELL_SIZE };
    SDL_RenderFillRect(renderer, &rect);
  }
}

void
Tetromino::reset_position()
{
  mFrameCoord = { 4 * constant::CELL_SIZE + constant::GRID_X0,
                  -2 * constant::CELL_SIZE + constant::GRID_Y0 };
  mAbsCoord = get_abs_coordinates(mFrameCoord, mLocalCoord);
  mHasLanded = false;
}

Tetromino::ElementCoord_t
Tetromino::get_abs_coordinates(const SDL_Point frameCoord, const ElementCoord_t localCoord) const
{
  ElementCoord_t absCoord;
  for (int idx = 0; idx < mSize; idx++) {
    absCoord[idx] = { localCoord[idx].x * constant::CELL_SIZE + frameCoord.x,
                      localCoord[idx].y * constant::CELL_SIZE + frameCoord.y };
  }
  return absCoord;
}

void
Tetromino::update(const Controller& controller, Grid& grid)
{
  if (controller.noAction()) {
    fall(grid);
  } else if (controller.mACTION) {
    rotate(grid);
  } else {
    move(controller, grid);
  }
}

void
Tetromino::fall(Grid& grid)
{
  SDL_Point      tmp_frameCoord{ mFrameCoord };
  ElementCoord_t tmp_localCoord{ mLocalCoord };

  tmp_frameCoord.y = mFrameCoord.y + mGravity;
  ElementCoord_t tmp_absCoord = get_abs_coordinates(tmp_frameCoord, tmp_localCoord);

  if (overlaps_blocks(tmp_absCoord, grid, true)) {
    mHasLanded = true;
    for (SDL_Point indices : get_containing_cell_indices(tmp_absCoord)) {
      grid.set_cell(indices.x, indices.y, true, mColor);
    }
  } else {
    mFrameCoord = tmp_frameCoord;
    mLocalCoord = tmp_localCoord;
    mAbsCoord = tmp_absCoord;
  }
}

void
Tetromino::rotate(const Grid& grid)
{
  ElementCoord_t tmp_localCoord{ mLocalCoord };
  for (int idx = 0; idx < mSize; idx++) {
    tmp_localCoord[idx].x = -mLocalCoord[idx].y + 2; // (x-x0) cos t - (y-y0) sin t
    tmp_localCoord[idx].y = mLocalCoord[idx].x;      // (x-x0) sin t + (y-y0) cos t
  }

  ElementCoord_t tmp_absCoord = get_abs_coordinates(mFrameCoord, tmp_localCoord);

  if (!has_collided(tmp_absCoord, grid)) {
    mLocalCoord = tmp_localCoord;
    mAbsCoord = tmp_absCoord;
  }
}

void
Tetromino::move(const Controller& controller, const Grid& grid)
{

  SDL_Point tmp_frameCoord{ mFrameCoord };
  if (controller.mRIGHT) {
    tmp_frameCoord.x += constant::CELL_SIZE;
  } else if (controller.mLEFT) {
    tmp_frameCoord.x -= constant::CELL_SIZE;
  } else if (controller.mDOWN) {
    tmp_frameCoord.y += constant::CELL_SIZE;
  }

  ElementCoord_t tmp_absCoord = get_abs_coordinates(tmp_frameCoord, mLocalCoord);

  if (!has_collided(tmp_absCoord, grid)) {
    mFrameCoord = tmp_frameCoord;
    mAbsCoord = tmp_absCoord;
  }
}

bool
Tetromino::has_collided(const ElementCoord_t absCoord, const Grid& grid) const
{
  auto out_of_bounds = [](SDL_Point coord) {
    return (coord.x < constant::GRID_X0) || (coord.x > constant::GRID_X1 - constant::CELL_SIZE);
  };

  if (std::any_of(absCoord.begin(), absCoord.end(), out_of_bounds)) {
    return true;
  }

  return overlaps_blocks(absCoord, grid);
}

bool
Tetromino::overlaps_blocks(const ElementCoord_t absCoord, const Grid& grid, bool below) const
{
  // The variable "below" indicates whether to check overlapping with the above or below blocks when
  // the tetromino is between adjacent vertical cells
  bool overlaps = false;
  for (SDL_Point indices : get_containing_cell_indices(absCoord)) {
    if (indices.y < 0) {
      break;
    }
    if (grid.get_cell(indices.x, indices.y + below).occupied) {
      overlaps = true;
    }
  }
  return overlaps;
}

Tetromino::ElementCoord_t
Tetromino::get_coord() const
{
  return mAbsCoord;
}

Tetromino::ElementCoord_t
Tetromino::get_containing_cell_indices(const ElementCoord_t absCoord) const
{
  // Gets the closest cell indices of the grid that contain the tetromino. If tetromino is between
  // two vertical cells it only retruns the one up
  ElementCoord_t cell_indices;

  for (std::size_t idx{ 0 }; idx < mSize; ++idx) {
    /* if (absCoord[idx].y < constant::GRID_Y0) { */
    /*   continue; */
    /* } */
    cell_indices[idx] = { (absCoord[idx].x - constant::GRID_X0) / constant::CELL_SIZE,
                          (absCoord[idx].y - constant::GRID_Y0) / constant::CELL_SIZE };
  }
  return cell_indices;
}

bool
Tetromino::has_landed() const
{
  return mHasLanded;
}

Color
Tetromino::get_color() const
{
  return mColor;
}
