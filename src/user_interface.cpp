#include "user_interface.h"

UserInterface::UserInterface(SDL_Renderer* renderer, TTF_Font* font)
  : next_piece_text_{ renderer, font, "NEXT", colors::WHITE, ui::kNextTextPosX, ui::kNextTextPosY }
  , score_text_{ renderer, font, "SCORE", colors::WHITE, ui::kScoreTextPosX, ui::kScoreTextPosY }
  , score_value_text_{ renderer,
                       font,
                       std::string(ui::kScoreValueMaxDigits, '0'),
                       colors::WHITE,
                       ui::kScoreValueTextPosX,
                       ui::kScoreValueTextPosY }
  , level_text_{ renderer, font, "LEVEL", colors::WHITE, ui::kLevelTextPosX, ui::kLevelTextPosY }
  , level_value_text_{ renderer,
                       font,
                       std::string(ui::kLevelValueMaxDigits, '0'),
                       colors::WHITE,
                       ui::kLevelValueTextPosX,
                       ui::kLevelValueTextPosY }
  , game_over_text_{ renderer, font, "GAME OVER", colors::WHITE, ui::kGameOverTextPosX, ui::kGameOverTextPosY }

{}

void
UserInterface::Render(bool game_over)
{
  next_piece_text_.Render();
  score_text_.Render();
  score_value_text_.Render();
  level_text_.Render();
  level_value_text_.Render();
  if (game_over) {
    // Overlay game over text over game grid
    game_over_text_.Render();
  }
}

void
UserInterface::UpdateScore(int new_score)
{
  score_value_text_.ChangeString(GetPaddedString(new_score, ui::kScoreValueMaxDigits));
}

void
UserInterface::UpdateLevel(int new_level)
{
  level_value_text_.ChangeString(GetPaddedString(new_level, ui::kLevelValueMaxDigits));
}

std::string
UserInterface::GetPaddedString(int new_value, int n_padding_zeros)
{
  auto not_padded = std::to_string(new_value);
  return std::string(n_padding_zeros - not_padded.length(), '0') + not_padded;
}
