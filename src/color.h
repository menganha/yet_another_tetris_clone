#ifndef COLOR_H
#define COLOR_H value

#include <SDL2/SDL.h>

namespace colors {

  constexpr SDL_Color BLACK{ 0x28, 0x2C, 0x34, 0xFF };
  constexpr SDL_Color WHITE{ 0xAB, 0xB2, 0xBF, 0xFF };
  constexpr SDL_Color RED{ 0xE0, 0x6C, 0x75, 0xFF };
  constexpr SDL_Color GREEN{ 0x98, 0xC3, 0x79, 0xFF };
  constexpr SDL_Color YELLOW{ 0xE5, 0xC0, 0x7B, 0xFF };
  constexpr SDL_Color BLUE{ 0x61, 0xAF, 0xEF, 0xFF };
  constexpr SDL_Color LILA{ 0xC6, 0x78, 0xDD, 0xFF };
  constexpr SDL_Color CYAN{ 0x56, 0xB6, 0xC2, 0xFF };

}

#endif /* ifndef COLOR_H */
