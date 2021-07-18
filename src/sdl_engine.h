#ifndef SDL_ENGINE_H
#define SDL_ENGINE_H

#include "constant.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class SDLEngine
{

public:
  SDLEngine();
  ~SDLEngine();
  void          Init();
  SDL_Renderer* renderer() const { return renderer_; }
  TTF_Font*     font() const { return font_; }

private:
  SDL_Renderer* renderer_;
  TTF_Font*     font_;
  SDL_Window*   window_;
};

#endif
