#include "color.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Text
{

public:
  Text(std::string text_string, SDL_Color text_color = colors::WHITE, int pos_x = 0, int pos_y = 0);
  ~Text();
  void Render(SDL_Renderer* renderer);
  void Load(SDL_Renderer* renderer);
  void ChangeString(SDL_Renderer* renderer, std::string new_string);

private:
  std::string  text_string_;
  SDL_Color    color_;
  SDL_Rect     rect_;
  SDL_Texture* texture_;
  TTF_Font*    font_;
};
