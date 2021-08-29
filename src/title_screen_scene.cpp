#include "title_screen_scene.h"
#include "color.h"
#include <algorithm>

TitleScreenScene::TitleScreenScene(SDL_Renderer* renderer, TTF_Font* font)
  : renderer_{ renderer }
  , font_{ font }
  , exit_{ false }
  , next_scene_type_{ SceneType::kNoScene }
  , input_{ 0, 10, 5 } // TODO: Test whether zero correspond to a infinite repeat rate
  , current_selected_item{ 0 }
  , menu_change_state{false}
  , menu_start_{ renderer, font, "START", colors::WHITE }
  , menu_quit_{ renderer, font, "QUIT", colors::WHITE }
  , menu_sound_{ "menu_select.wav" }
{
  //  Centers the Menu items
  menu_start_.Move((constant::kScreenWidth - menu_start_.Width()) / 2, kStartYpos);
  menu_quit_.Move((constant::kScreenWidth - menu_quit_.Width()) / 2, kQuitYpos);
  menu_start_.ChangeColor({ 0xFF, 0xFF, 0xFF, 0xFF });
}

void
TitleScreenScene::RunLoop()
{
  while (not exit_) {
    Update();
    Draw();
  }
}

SceneType
TitleScreenScene::NextSceneType() const
{
  return next_scene_type_;
}

void
TitleScreenScene::Update()
{
  input_.Update();

  // logic
  int previous_selected_item = current_selected_item;
  menu_change_state = false;
  if (input_.Up()) {
    current_selected_item -= 1;
    current_selected_item = std::max(current_selected_item, 0);
  } else if (input_.Down()) {
    current_selected_item += 1;
    current_selected_item = std::min(current_selected_item, 1); // maximum number of menu items - 1
  }
  if (current_selected_item != previous_selected_item) {
    menu_sound_.Play();
    menu_change_state = true;
  }

  if (input_.Action() and current_selected_item == 0) {
    exit_ = true;
    next_scene_type_ = SceneType::kMainGame;
  } else if ((input_.Action() and current_selected_item == 1) or input_.Quit()) {
    exit_ = true;
    next_scene_type_ = SceneType::kNoScene;
  }
}

void
TitleScreenScene::Draw()
{

  if (menu_change_state) {
    if (current_selected_item == 0) {
      menu_start_.ChangeColor({ 0xFF, 0xFF, 0xFF, 0xFF });
      menu_quit_.ChangeColor(colors::WHITE);
    } else if (current_selected_item == 1) {
      menu_start_.ChangeColor(colors::WHITE);
      menu_quit_.ChangeColor({ 0xFF, 0xFF, 0xFF, 0xFF });
    }
  }

  SDL_SetRenderDrawColor(renderer_, colors::BLACK.r, colors::BLACK.g, colors::BLACK.b, colors::BLACK.a);
  SDL_RenderClear(renderer_);
  menu_start_.Render();
  menu_quit_.Render();
  SDL_RenderPresent(renderer_);
}
