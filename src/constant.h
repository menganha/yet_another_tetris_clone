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

  // UI elements
  constexpr int kNextTextPosX = 500;
  constexpr int kNextTextPosY = 80;
  constexpr int kNextPiecePosX = 492;
  constexpr int kNextPiecePosY = 120;

  constexpr int kScoreTextPosX = 50;
  constexpr int kScoreTextPosY = 80;
  constexpr int kScoreValueTextPosX = 42;
  constexpr int kScoreValueTextPosY = 130;

  constexpr int kLevelTextPosX = 50;
  constexpr int kLevelTextPosY = 200;
  constexpr int kLevelValueTextPosX = 90;
  constexpr int kLevelValueTextPosY = 250;

  constexpr int kGameOverTextPosX = kGridX0 + 26;
  constexpr int kGameOverTextPosY = (kGridY1 - kGridY0) / 2;

} // namespace constant

#endif
