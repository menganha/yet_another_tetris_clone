#ifndef COLOR_H
#define COLOR_H value

#include <cstdint>

struct Color
{
  std::uint_fast8_t red;
  std::uint_fast8_t green;
  std::uint_fast8_t blue;
  std::uint_fast8_t alpha{ 0xFF };
};

namespace colors {

constexpr Color BLACK{ 0x28, 0x2C, 0x34 };
constexpr Color WHITE{ 0xAB, 0xB2, 0xBF };
constexpr Color RED{ 0xE0, 0x6C, 0x75 };
constexpr Color GREEN{ 0x98, 0xC3, 0x79 };
constexpr Color YELLOW{ 0xE5, 0xC0, 0x7B };
constexpr Color BLUE{ 0x61, 0xAF, 0xEF };
constexpr Color LILA{ 0xC6, 0x78, 0xDD };
constexpr Color CYAN{ 0x56, 0xB6, 0xC2 };

}

#endif /* ifndef COLOR_H */
