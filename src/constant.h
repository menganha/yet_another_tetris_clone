#ifndef CONSTANT_H
#define CONSTANT_H

#include <array>

namespace constant {

  constexpr int kScreenWidth = 640;
  constexpr int kScreenSize = 480;
  constexpr int kCellSize = 23;
  constexpr int kNCols = 10;
  constexpr int kNRows = 20;
  constexpr int kGridX0 = kScreenWidth / 2 - kNCols * kCellSize / 2;
  constexpr int kGridY0 = kScreenSize / 2 - kNRows * kCellSize / 2;
  constexpr int kGridX1 = kGridX0 + kNCols * kCellSize;
  constexpr int kGridY1 = kGridY0 + kNRows * kCellSize;

}

#endif
