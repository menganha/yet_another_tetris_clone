#include "in_game_menu.h"
#include "color.h"

InGameMenu::InGameMenu(SDL_Renderer* renderer, TTF_Font* font)
  : current_selected_item{ 0 }
  , renderer_{ renderer }
  , game_over_text_{ renderer, font, "GAME OVER", colors::WHITE }
  , pause_text_{ renderer, font, "PAUSE", colors::WHITE }
  , play_again_text_{ renderer, font, "play again", colors::WHITE }
  , exit_text_{ renderer_, font, "exit", colors::WHITE }
  , resume_text_{ renderer_, font, "resume", colors::WHITE }
{
  game_over_text_.Move(pos_x + (width - game_over_text_.Width()) / 2, pos_y + 10);
  pause_text_.Move(pos_x + (width - pause_text_.Width()) / 2, pos_y + 10);

  play_again_text_.Move(pos_x + (width - play_again_text_.Width()) / 2, pos_y + 50);
  resume_text_.Move(pos_x + (width - resume_text_.Width()) / 2, pos_y + 50);
  exit_text_.Move(pos_x + (width - exit_text_.Width()) / 2, pos_y + 70);
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
  SDL_Rect rect{ pos_x, pos_y, width, height };
  // inside
  SDL_SetRenderDrawColor(renderer_, colors::BLACK.r, colors::BLACK.g, colors::BLACK.b, colors::BLACK.a);
  SDL_RenderFillRect(renderer_, &rect);
  // outside
  SDL_SetRenderDrawColor(renderer_, colors::WHITE.r, colors::WHITE.g, colors::WHITE.b, 0x20);
  SDL_RenderDrawRect(renderer_, &rect);
  for (int idx{ 1 }; idx < 2; ++idx) {
    rect = { pos_x - idx, pos_y - idx, width + 2 * idx, height + 2 * idx };
    SDL_RenderDrawRect(renderer_, &rect);
  }

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
