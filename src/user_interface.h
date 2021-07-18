#ifndef UI_H
#define UI_H

#include "constant.h"
#include "text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class UserInterface
{
public:
  UserInterface(SDL_Renderer* renderer, TTF_Font* font);
  void Render(bool game_over);
  void UpdateScore(int new_score);
  void UpdateLevel(int new_level);

private:
  Text        next_piece_text_;
  Text        score_text_;
  Text        score_value_text_;
  Text        level_text_;
  Text        level_value_text_;
  Text        game_over_text_;

  std::string GetPaddedString(int new_value, int n_padding_zeros);
};

// UI elements position
namespace ui {

  constexpr int kScoreValueMaxDigits = 6;
  constexpr int kLevelValueMaxDigits = 2;

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
  constexpr int kLevelValueTextPosX = 80;
  constexpr int kLevelValueTextPosY = 250;

  constexpr int kGameOverTextPosX = constant::kGridX0 + 26;
  constexpr int kGameOverTextPosY = (constant::kGridY1 - constant::kGridY0) / 2;
}

#endif
