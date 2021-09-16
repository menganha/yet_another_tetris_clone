#include "in_game_menu.h"

InGameMenu::InGameMenu(SDL_Renderer* renderer, TTF_Font* font)
  : current_selected_item{ 0 }
  , renderer_{ renderer }
  , game_over_text_{ renderer, font, "GAME OVER", colors::WHITE }
  , pause_text_{ renderer, font, "PAUSE", colors::WHITE }
  , play_again_text_{ renderer, font, "play again", colors::WHITE }
  , exit_text_{ renderer_, font, "exit", colors::WHITE }
  , resume_text_{ renderer_, font, "resume", colors::WHITE }
{
  game_over_text_.Move(pos_x, pos_y);
  pause_text_.Move(pos_x, pos_y);
  play_again_text_.Move(pos_x, pos_y + 20);
  resume_text_.Move(pos_x, pos_y + 20);
  exit_text_.Move(pos_x, pos_y + 40);
}

void
InGameMenu::Update()
{
  if (current_selected_item == 0) {
    play_again_text_.ChangeColor(colors::TRUE_WHITE);
    resume_text_.ChangeColor(colors::TRUE_WHITE);
    exit_text_.ChangeColor(colors::WHITE);
  } else if (current_selected_item == 1) {
    play_again_text_.ChangeColor(colors::WHITE);
    resume_text_.ChangeColor(colors::WHITE);
    exit_text_.ChangeColor(colors::TRUE_WHITE);
  }
}

void
InGameMenu::Render(bool const game_over)
{
  // If game over is true then render the game over menu otherwise is the pause menu
  if (game_over) {
    game_over_text_.Render();
    play_again_text_.Render();
  } else {
    pause_text_.Render();
    resume_text_.Render();
  }
  exit_text_.Render();
}
