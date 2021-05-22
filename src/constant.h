#ifndef CONSTANT_H
#define CONSTANT_H

#include "color.h"
#include <array>

namespace constant {

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;
constexpr int CELL_SIZE = 20;
constexpr int N_HORIZ_CELLS = 10;
constexpr int N_VERT_CELLS = 20;
constexpr int GRID_X0 =
  SCREEN_WIDTH / 2 - constant::N_HORIZ_CELLS * constant::CELL_SIZE / 2;
constexpr int GRID_Y0 =
  SCREEN_HEIGHT / 2 - constant::N_VERT_CELLS * constant::CELL_SIZE / 2;
constexpr int GRID_X1 = GRID_X0 + constant::N_HORIZ_CELLS * constant::CELL_SIZE;
constexpr int GRID_Y1 = GRID_Y0 + constant::N_VERT_CELLS * constant::CELL_SIZE;

// Colors
constexpr Color BLACK{ 0x28, 0x2C, 0x34 };
constexpr Color WHITE{ 0xAB, 0xB2, 0xBF };
constexpr Color BLUE{ 0x56, 0xB6, 0xC2 };

} // namespace constant

#endif
