#ifndef TETRAMINO_H
#define TETRAMINO_H

#include "constant.h"
#include "controller.h"
#include <SDL2/SDL.h>

class Tetramino
{
  public:
    Tetramino();
    ~Tetramino();

    void render(SDL_Renderer* renderer);
    void update(Controller& controller);

  private:
    static const int mSize = 4;
    SDL_Rect mShape[mSize];
};

#endif
