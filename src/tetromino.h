#ifndef TETRAMINO_H
#define TETRAMINO_H

#include "constant.h"
#include "controller.h"
#include <SDL2/SDL.h>
#include <algorithm>

class Tetromino
{

  private:
    static const int mSize = 4;
    static const int mDir = 4;

  public:
    Tetromino(std::array<SDL_Point, mSize> coordList);
    /* Tetromino(std::initializer_list<SDL_Point> coordList); */
    ~Tetromino();

    void render(SDL_Renderer* renderer);
    void update(Controller& controller);
    bool has_landed();
    void set_gravity(const int gravity);
    void resetPos();

  private:
    void rotate();
    int mGravity; // Set it to a positive integer
    std::array<SDL_Rect, mSize> mShape;
    const std::array<SDL_Point, mSize> mLocalCoord;
};

#endif
