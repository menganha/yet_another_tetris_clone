#include "user_interface.h"

UserInterface::UserInterface()
  : next_piece_text_{ "NEXT", colors::WHITE, ui::kNextTextPosX, ui::kNextTextPosY }
  , score_text_{ "SCORE", colors::WHITE, ui::kScoreTextPosX, ui::kScoreTextPosY }
  , score_value_text_{ std::string(ui::kScoreValueMaxDigits, '0'),
                       colors::WHITE,
                       ui::kScoreValueTextPosX,
                       ui::kScoreValueTextPosY }
  , level_text_{ "LEVEL", colors::WHITE, ui::kLevelTextPosX, ui::kLevelTextPosY }
  , level_value_text_{ std::string(ui::kLevelValueMaxDigits, '0'),
                       colors::WHITE,
                       ui::kLevelValueTextPosX,
                       ui::kLevelValueTextPosY }
  , game_over_text_{ "GAME OVER", colors::WHITE, ui::kGameOverTextPosX, ui::kGameOverTextPosY }

{}

void
UserInterface::Load(SDL_Renderer* renderer)
{
  // Cannot load on constructor as TTF module must be initialized first
  next_piece_text_.Load(renderer);
  score_text_.Load(renderer);
  score_value_text_.Load(renderer);
  level_text_.Load(renderer);
  level_value_text_.Load(renderer);
  game_over_text_.Load(renderer);
}

void
UserInterface::Render(SDL_Renderer* renderer, bool game_over)
{
  next_piece_text_.Render(renderer);
  score_text_.Render(renderer);
  score_value_text_.Render(renderer);
  level_text_.Render(renderer);
  level_value_text_.Render(renderer);
  if (game_over){
    game_over_text_.Render(renderer);
  }
}

void
UserInterface::UpdateScore(SDL_Renderer* renderer, int new_score)
{
  score_value_text_.ChangeString(renderer, GetPaddedString(new_score, ui::kScoreValueMaxDigits));
}

void
UserInterface::UpdateLevel(SDL_Renderer* renderer, int new_level)
{
  level_value_text_.ChangeString(renderer, GetPaddedString(new_level, ui::kLevelValueMaxDigits));
}

std::string
UserInterface::GetPaddedString(int new_value, int n_padding_zeros)
{
  auto not_padded = std::to_string(new_value);
  return std::string(n_padding_zeros - not_padded.length(), '0') + not_padded;
}
