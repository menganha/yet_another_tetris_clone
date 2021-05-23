#ifndef TETROMINO_H
#define TETROMINO_H

#include "constant.h"
#include "controller.h"
#include <SDL2/SDL.h>
#include <algorithm>

class Tetromino
{

private:
  static const int mSize = 4;
  static const int mDir = 4;

public:
  using tetrominoRectCoord_t = std::array<SDL_Rect, mSize>;
  using tetrominoPosCoord_t = std::array<SDL_Point, mSize>;

  Tetromino(std::array<SDL_Point, mSize> coordList);
  ~Tetromino();

  void render(SDL_Renderer* renderer);
  void update(Controller& controller);
  bool has_landed();
  void set_gravity(const int gravity);
  void resetPos();
  tetrominoRectCoord_t get_coord() const;
  tetrominoPosCoord_t get_containing_cell_indices() const;

private:
  void rotate();
  int mGravity; // Set it to a positive integer
  Color mColor;
  tetrominoRectCoord_t mRects;
  const tetrominoPosCoord_t mLocalCoord;
};

#endif
