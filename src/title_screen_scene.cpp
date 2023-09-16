#include "title_screen_scene.h"
#include "color.h"
#include <SDL2/SDL_image.h>
#include "utils.h"
#include <algorithm>

TitleScreenScene::TitleScreenScene(SDL_Renderer* renderer, TTF_Font* font)
  : renderer_{ renderer }
  , font_{ font }
  , exit_{ false }
  , next_scene_type_{ SceneType::kNoScene }
  , input_{ 0, 10, 5 } // TODO: Test whether zero correspond to a infinite repeat rate
  , current_selected_item{ 0 }
  , menu_change_state{ false }
  , menu_start_{ renderer, font, "START", colors::WHITE }
  , menu_quit_{ renderer, font, "QUIT", colors::WHITE }
  , acronym_{ renderer, font, "(yet another tetris clone)", colors::WHITE }
  , game_title_image_texture_{ nullptr }
  , game_title_image_position_{ 0, 0, 0, 0 }
  , menu_sound_{ "menu_select.wav" }
  , menu_confirm_sound_{ "menu_confirm.wav" }
{
  //  Centers the Menu items
  menu_start_.Move((constant::kScreenWidth - menu_start_.Width()) / 2, kStartYpos);
  menu_quit_.Move((constant::kScreenWidth - menu_quit_.Width()) / 2, kQuitYpos);
  menu_start_.ChangeColor(colors::TRUE_WHITE);
  acronym_.Move((constant::kScreenWidth - acronym_.Width()) / 2, kAcronymYpos);
  get_image();
}

TitleScreenScene::~TitleScreenScene()
{
  SDL_DestroyTexture(game_title_image_texture_);
  game_title_image_texture_ = nullptr;
}

void
TitleScreenScene::get_image()
{
  // We don't have a class for loading images since we use it only for the title screen
  // This should suffice. Freeing of the title image is done on this class constructor
  SDL_Surface* surface = IMG_Load("../title.png");
  game_title_image_texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
  game_title_image_position_.w = surface->w;
  game_title_image_position_.h = surface->h;
  game_title_image_position_.x = (constant::kScreenWidth - game_title_image_position_.w) / 2;
  game_title_image_position_.y = kTitleYpos;
  SDL_FreeSurface(surface);
}

void
TitleScreenScene::RunLoop()
{

  while (not exit_) {
    input_.Update();
    Update();
    Draw();
  }
  exit_ = false;
  current_selected_item = 0;
  menu_change_state = false;
  input_.Reset();
  utils::Wait(10, renderer_);
}

SceneType
TitleScreenScene::NextSceneType() const
{
  return next_scene_type_;
}

void
TitleScreenScene::Update()
{

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

  if ((input_.A() or input_.Pause()) and current_selected_item == 0) {
    exit_ = true;
    next_scene_type_ = SceneType::kMainGame;
    menu_confirm_sound_.Play();
  } else if (((input_.A() or input_.Pause()) and current_selected_item == 1) or input_.Quit()) {
    exit_ = true;
    next_scene_type_ = SceneType::kNoScene;
  }
}

void
TitleScreenScene::Draw()
{

  if (menu_change_state) {
    if (current_selected_item == 0) {
      menu_start_.ChangeColor(colors::TRUE_WHITE);
      menu_quit_.ChangeColor(colors::WHITE);
    } else if (current_selected_item == 1) {
      menu_start_.ChangeColor(colors::WHITE);
      menu_quit_.ChangeColor(colors::TRUE_WHITE);
    }
  }

  SDL_SetRenderDrawColor(renderer_, colors::BLACK.r, colors::BLACK.g, colors::BLACK.b, colors::BLACK.a);
  SDL_RenderClear(renderer_);
  SDL_RenderCopy(renderer_, game_title_image_texture_, NULL, &game_title_image_position_);
  menu_start_.Render();
  menu_quit_.Render();
  acronym_.Render();

  SDL_RenderPresent(renderer_);
}
