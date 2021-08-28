#ifndef TITLE_SCREEN_SCENE_H
#define TITLE_SCREEN_SCENE_H

#include "constant.h"
#include "input.h"
#include "scene.h"
#include "scene_type.h"
#include "text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TitleScreenScene : public Scene
{
public:
  TitleScreenScene(SDL_Renderer* renderer, TTF_Font* font);
  void      RunLoop();
  SceneType NextSceneType() const;

private:
  SDL_Renderer*        renderer_;
  TTF_Font*            font_;
  bool                 exit_;
  SceneType            next_scene_type_;
  Input                input_;
  Text                 menu_start_;
  Text                 menu_quit_;
  void                 Update();
  void                 Draw();
  static constexpr int kStartYpos = constant::kScreenHeight / 2;
  static constexpr int kQuitYpos = kStartYpos + 30;
};

#endif
