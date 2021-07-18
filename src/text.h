#ifndef TEXT_H
#define TEXT_H

#include "color.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Text
{

public:
  Text(SDL_Renderer* renderer,
       TTF_Font*     font,
       std::string   text_string,
       SDL_Color     text_color = colors::WHITE,
       int           pos_x = 0,
       int           pos_y = 0);
  ~Text();
  void Render();
  void ChangeString(std::string new_string);

private:
  void          Load();
  SDL_Renderer* renderer_;
  TTF_Font*     font_;
  std::string   text_string_;
  SDL_Color     color_;
  SDL_Rect      rect_;
  SDL_Texture*  texture_;
};

#endif
