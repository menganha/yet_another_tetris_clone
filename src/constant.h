#ifndef CONSTANT_H
#define CONSTANT_H

#include "color.h"
#include <array>

namespace constant {

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;
constexpr int CELL_SIZE = 16;
constexpr int GRID_WIDTH = 10;
constexpr int GRID_HEIGHT = 20;

// Colors
constexpr Color BLACK{ 0x28, 0x2C, 0x34 };
constexpr Color WHITE{ 0xAB, 0xB2, 0xBF };
constexpr Color BLUE{ 0x56, 0xB6, 0xC2 };

} // namespace constant

#endif
