#ifndef L_TEXTURE_H
#define L_TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class LTexture
{
  private:
    SDL_Texture* mTexture;
    SDL_Renderer*& mRenderer;
    int mWidth;
    int mHeight;

  public:
    LTexture(SDL_Renderer *&renderer);                  // Initializes variables
    ~LTexture();                                       // Deallocates memory
    bool loadFromFile(std::string path);               // Loads image at specified path
    void free();                                       // Deallocates texture
    void setColor(Uint8 red, Uint8 green, Uint8 blue); // Set color modulation
    void setBlendMode(SDL_BlendMode blending);         // Set blending
    void setAlpha(Uint8 alpha);                        // Set alpha modulation
    void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL,
                SDL_RendererFlip flip = SDL_FLIP_NONE); // Renders texture at given point
    int getWidth();                                     // Gets image dimensions
    int getHeight();
#if defined(SDL_TTF_MAJOR_VERSION)
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor); // Creates image from font string
#endif
};

#endif
