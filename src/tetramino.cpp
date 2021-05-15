#include "tetramino.h"

// TODO: create a enum with all the possiblities starting from 0,0

Tetramino::Tetramino()
  : mShape{ { 0, 0, constant::CELL_SIZE, constant::CELL_SIZE },
            { 0, constant::CELL_SIZE, constant::CELL_SIZE, constant::CELL_SIZE },
            { constant::CELL_SIZE, constant::CELL_SIZE, constant::CELL_SIZE, constant::CELL_SIZE },
            { 2 * constant::CELL_SIZE, constant::CELL_SIZE, constant::CELL_SIZE, constant::CELL_SIZE } }
{}

Tetramino::~Tetramino() {}

void
Tetramino::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x3B, 0x42, 0x48, 0x00);
    SDL_RenderFillRects(renderer, mShape, mSize);
}

void
Tetramino::update(Controller& controller)
{
    for (int idx = 0; idx < mSize; ++idx) {
        
        if (controller.mRIGHT) {
            mShape[idx].x = mShape[idx].x + constant::CELL_SIZE;
        } else if (controller.mLEFT) {
            mShape[idx].x = mShape[idx].x - constant::CELL_SIZE;
        }
    }
}
