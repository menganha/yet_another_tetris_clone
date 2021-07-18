#ifndef TITLE_SCREEN_SCENE_H
#define TITLE_SCREEN_SCENE_H

#include "scene.h"
#include <SDL2/SDL.h>

class TitleScreenScene : public Scene
{
public:
  TitleScreenScene(SDL_Renderer* renderer);
  void RunLoop();

private:
  SDL_Renderer* renderer_;
  /* void Update(); */
  /* void Render(); */
  /* void Draw(); */
};

#endif
