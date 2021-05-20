#include "tetromino.h"

Tetromino::Tetromino(std::array<SDL_Point, mSize> coordList)
  : mGravity{ 3 }
  , mLocalCoord{ coordList }
{
    /* std::copy(coordList.begin(), coordList.end(), mLocalCoord); */
    resetPos();
}

Tetromino::~Tetromino() {}

void
Tetromino::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x3B, 0x42, 0x48, 0x00);
    SDL_RenderFillRects(renderer, mShape.data(), mSize);
}

void
Tetromino::resetPos()
{
    for (int idx = 0; idx < mSize; idx++) {
        mShape[idx] = { mLocalCoord[idx].x * constant::CELL_SIZE + 40,
                        mLocalCoord[idx].y * constant::CELL_SIZE,
                        constant::CELL_SIZE,
                        constant::CELL_SIZE };
    }
}

void
Tetromino::update(Controller& controller)
{
    if (controller.mRIGHT && std::any_of(mShape.begin(), mShape.end(), [](SDL_Rect rect) {
            return rect.x >= constant::SCREEN_WIDTH - constant::CELL_SIZE;
        })) {
        return;
    }
    if (controller.mLEFT &&
        std::any_of(mShape.begin(), mShape.end(), [](SDL_Rect rect) { return rect.x <= 0; })) {
        return;
    }

    for (int idx = 0; idx < mSize; ++idx) {
        if (controller.mRIGHT) {
            mShape[idx].x = mShape[idx].x + constant::CELL_SIZE;
        } else if (controller.mLEFT) {
            mShape[idx].x = mShape[idx].x - constant::CELL_SIZE;
        }
        /* else if (controller.mDOWN) { */
        /*     mShape[idx].y = mShape[idx].y + constant::CELL_SIZE; */
        /* } */
        mShape[idx].y = mShape[idx].y + mGravity;
    }
}

bool
Tetromino::has_landed()
{
    return std::any_of(
      mShape.begin(), mShape.end(), [](SDL_Rect rect) { return rect.y > constant::SCREEN_HEIGHT; });
    /* resetPos(); */
}
