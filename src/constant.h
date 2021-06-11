#ifndef CONSTANT_H
#define CONSTANT_H

#include <array>

namespace constant {

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;
constexpr int CELL_SIZE = 23;
constexpr int N_COLS = 10;
constexpr int N_ROWS = 20;
constexpr int GRID_X0 =
  SCREEN_WIDTH / 2 - constant::N_COLS * constant::CELL_SIZE / 2;
constexpr int GRID_Y0 =
  SCREEN_HEIGHT / 2 - constant::N_ROWS * constant::CELL_SIZE / 2;
constexpr int GRID_X1 = GRID_X0 + constant::N_COLS * constant::CELL_SIZE;
constexpr int GRID_Y1 = GRID_Y0 + constant::N_ROWS * constant::CELL_SIZE;

} // namespace constant

#endif
