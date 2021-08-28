#include "title_screen_scene.h"
#include "color.h"

TitleScreenScene::TitleScreenScene(SDL_Renderer* renderer, TTF_Font* font)
  : renderer_{ renderer }
  , font_{ font }
  , exit_{ false }
  , next_scene_type_{ SceneType::kNoScene }
  , input_{ 0, 10, 5 } // TODO: Test whether zero correspond to a infinite repeat rate
  , menu_start_{ renderer, font, "START", colors::WHITE }
  , menu_quit_{ renderer, font, "QUIT", colors::WHITE }
{
  //  Centers the Menu items
  menu_start_.Move((constant::kScreenWidth - menu_start_.Width()) / 2, kStartYpos);
  menu_quit_.Move((constant::kScreenWidth - menu_quit_.Width()) / 2, kQuitYpos);
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
  if (input_.Action()) {
    exit_ = true;
    next_scene_type_ = SceneType::kMainGame;
  } else if (input_.Quit()){
    exit_ = true;
    next_scene_type_ = SceneType::kNoScene;
  }
}

void
TitleScreenScene::Draw()
{
  SDL_SetRenderDrawColor(renderer_, colors::BLACK.r, colors::BLACK.g, colors::BLACK.b, colors::BLACK.a);
  SDL_RenderClear(renderer_);
  menu_start_.Render();
  menu_quit_.Render();
  SDL_RenderPresent(renderer_);
}
