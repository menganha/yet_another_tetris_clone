#include "text.h"

Text::Text(std::string text_string, SDL_Color text_color, int pos_x, int pos_y)
  : text_string_{ text_string }
  , color_{ text_color }
  , rect_{ pos_x, pos_y, 0, 0 }
  , texture_{ nullptr }
  , font_{TTF_OpenFont("font/PressStart2P.ttf", 20)}

{}

Text::~Text()
{
  SDL_DestroyTexture(texture_);
}

void
Text::Load(SDL_Renderer* renderer)
{
  // Load the text into a surface. Needs renderer
  SDL_Surface* surface = TTF_RenderText_Solid(font_, text_string_.c_str(), color_);
  rect_.w = surface->w;
  rect_.h = surface->h;
  texture_ = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

void
Text::Render(SDL_Renderer* renderer)
{
  // TODO: Should I add a check here if the texture is nullptr?
  SDL_RenderCopy(renderer, texture_, NULL, &rect_);
}
  
void 
Text::ChangeString(SDL_Renderer* renderer, std::string new_string){
  text_string_ = new_string;
  Load(renderer);
}

