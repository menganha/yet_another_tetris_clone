#include "tetromino.h"

Tetromino::Tetromino(std::array<SDL_Point, mSize> coordList)
  : mGravity{ 2 }
  , mColor{ constant::BLUE }
  , mLocalCoord{ coordList }
{
  resetPos();
}

Tetromino::~Tetromino() {}

void
Tetromino::render(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, mColor.red, mColor.green, mColor.blue, mColor.alpha);
  SDL_RenderFillRects(renderer, mRects.data(), mSize);
}

void
Tetromino::resetPos()
{
  for (int idx = 0; idx < mSize; idx++) {
    mRects[idx] = { (mLocalCoord[idx].x+3) * constant::CELL_SIZE + constant::GRID_X0,
                    (mLocalCoord[idx].y-2) * constant::CELL_SIZE + constant::GRID_Y0,
                    constant::CELL_SIZE,
                    constant::CELL_SIZE };
  }
}

void
Tetromino::update(Controller& controller)
{
  if (controller.mRIGHT && std::any_of(mRects.begin(), mRects.end(), [](SDL_Rect rect) {
        return rect.x >= constant::GRID_X1 - constant::CELL_SIZE;
      })) {
    return;
  }
  if (controller.mLEFT && std::any_of(mRects.begin(), mRects.end(), [](SDL_Rect rect) {
        return rect.x <= constant::GRID_X0;
      })) {
    return;
  }

  for (int idx = 0; idx < mSize; ++idx) {
    if (controller.mRIGHT) {
      mRects[idx].x = mRects[idx].x + constant::CELL_SIZE;
    } else if (controller.mLEFT) {
      mRects[idx].x = mRects[idx].x - constant::CELL_SIZE;
    }
    /* else if (controller.mDOWN) { */
    /*     mShape[idx].y = mShape[idx].y + constant::CELL_SIZE; */
    /* } */
    mRects[idx].y = mRects[idx].y + mGravity;
  }
}

bool
Tetromino::has_landed()
{
  return std::any_of(
    mRects.begin(), mRects.end(), [](SDL_Rect rect) { return rect.y > constant::GRID_Y1; });
}

Tetromino::tetrominoRectCoord_t
Tetromino::get_coord() const
{
  return mRects;
}

Tetromino::tetrominoPosCoord_t
Tetromino::get_containing_cell_indices() const
{
  // Gets the closest cell indices of the grid that contain the tetromino
  tetrominoPosCoord_t cell_indices;

  for (std::size_t idx{ 0 }; idx < mSize; ++idx) {
    cell_indices[idx].x = (mRects[idx].x - constant::GRID_X0) / constant::CELL_SIZE;
    cell_indices[idx].y = (mRects[idx].y - constant::GRID_Y0) / constant::CELL_SIZE;
  }
  return cell_indices;
}
