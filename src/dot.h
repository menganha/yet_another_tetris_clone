#ifndef DOT_H
#define DOT_H

#include "l_texture.h"
#include <SDL2/SDL.h>

class Dot
{
  private:
    LTexture mDotTexture; // Texture
    int mPosX, mPosY;     // The X and Y offsets of the dot
    int mVelX, mVelY;     // The velocity of the dot

  public:
    // The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    // Maximum axis velocity of the dot
    static const int DOT_VEL = 10;

    // Initializes the variables
    Dot(SDL_Renderer *&renderer);

    // Takes key presses and adjusts the dot's velocity
    void handleEvent(SDL_Event &e);

    // Moves the dot
    void move();

    // Shows the dot on the screen relative to the camera
    void render(int camX, int camY);

    // Position accessors
    int getPosX();
    int getPosY();

    bool load();
};

#endif
