#ifndef TITLE_SCREEN_SCENE_H
#define TITLE_SCREEN_SCENE_H

#include "constant.h"
#include "input.h"
#include "scene.h"
#include "scene_type.h"
#include "sound.h"
#include "text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <filesystem>

class TitleScreenScene : public Scene
{
public:
  TitleScreenScene(SDL_Renderer* renderer, TTF_Font* font);
  ~TitleScreenScene();
  void      RunLoop();
  SceneType NextSceneType() const;

private:
  SDL_Renderer*        renderer_;
  TTF_Font*            font_;
  bool                 exit_;
  SceneType            next_scene_type_;
  Input                input_;
  int                  current_selected_item; // represents the menu item selected
  bool                 menu_change_state;
  Text                 menu_start_;
  Text                 menu_quit_;
  Text                 acronym_;
  SDL_Texture*         game_title_image_texture_;
  SDL_Rect             game_title_image_position_;
  Sound                menu_sound_;
  void                 Update();
  void                 Draw();
  static constexpr int kTitleYpos = constant::kScreenHeight / 2 - 80;
  static constexpr int kAcronymYpos = kTitleYpos + 65;
  static constexpr int kStartYpos = kAcronymYpos + 100;
  static constexpr int kQuitYpos = kStartYpos + 30;

  //
  void                 get_image();
};

#endif
