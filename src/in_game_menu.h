#ifndef IN_GAME_MENU_H
#define IN_GAME_MENU_H

#include "constant.h"
#include "text.h"
#include <SDL2/SDL.h>

class InGameMenu
{
public:
  InGameMenu(SDL_Renderer* renderer, TTF_Font* font);
  void Render(bool const game_over);
  void Update();
  int  current_selected_item;

private:
  SDL_Renderer*        renderer_;
  Text                 game_over_text_;
  Text                 pause_text_;
  Text                 play_again_text_;
  Text                 exit_text_;
  Text                 resume_text_;

  static constexpr int width = constant::kScreenWidth * 0.6;
  static constexpr int pos_x = (constant::kScreenWidth - width) / 2;
  static constexpr int height = 50;
  static constexpr int pos_y = (constant::kScreenHeight - height) / 2;
};

#endif
