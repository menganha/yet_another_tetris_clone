#include "constant.h"
#include <SDL2/SDL.h>

class Tetramino
{
  public:
    Tetramino();
    ~Tetramino();

    void render(SDL_Renderer* renderer);
    void update();

  private:
    static const int mSize = 4;
    SDL_Rect mShape[mSize];
};
