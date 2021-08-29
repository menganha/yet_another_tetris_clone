#include "text.h"

Text::Text(SDL_Renderer* renderer, TTF_Font* font, std::string text_string, SDL_Color text_color, int pos_x, int pos_y)
  : renderer_{ renderer }
  , font_{ font }
  , text_string_{ text_string }
  , color_{ text_color }
  , rect_{ pos_x, pos_y, 0, 0 }
  , texture_{ nullptr }
{
  Load();
}

Text::~Text()
{
  SDL_DestroyTexture(texture_);
}

void
Text::Load()
{
  // Load the text into a surface. Needs renderer
  SDL_Surface* surface = TTF_RenderText_Solid(font_, text_string_.c_str(), color_);
  rect_.w = surface->w;
  rect_.h = surface->h;
  texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
  SDL_FreeSurface(surface);
}

void
Text::Render()
{
  // TODO: Should I add a check here if the texture is nullptr?
  SDL_RenderCopy(renderer_, texture_, NULL, &rect_);
}

void
Text::ChangeString(std::string new_string)
{
  text_string_ = new_string;
  Load();
}

void
Text::ChangeColor(SDL_Color new_color)
{
  color_ = new_color;
  Load();
}

void
Text::Move(int new_pos_x, int new_pos_y)
{
  rect_.x = new_pos_x;
  rect_.y = new_pos_y;
}
