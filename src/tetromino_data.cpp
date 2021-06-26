#include "tetromino_data.h"

tdata::Coord extern const tdata::kDefinition[tdata::TotalTypes] = {
  { { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, // T block
  { { { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, // L block
  { { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }, // J block
  { { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } } }, // Z block
  { { { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } } }, // S block
  { { { 1, 0 }, { 2, 0 }, { 1, 1 }, { 2, 1 } } }, // I block
  { { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } } }  // O block
};

void
tdata::RenderBlock(SDL_Renderer* renderer, int const pos_x, int const pos_y, SDL_Color color)
{
  SDL_Rect rect{ pos_x, pos_y, constant::kCellSize, constant::kCellSize };
  // inside
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &rect);
  // outline
  SDL_SetRenderDrawColor(renderer, color.r * 0.7, color.g * 0.7, color.b * 0.7, color.a);
  SDL_RenderDrawRect(renderer, &rect);
}

SDL_Point
tdata::AdjustedInitialPosition(tdata::TetrominoType const type, int pos_x, int pos_y)
{
  if (type == tdata::I_block) {
    pos_y -= constant::kCellSize;
  }
  return { pos_x, pos_y };
}
