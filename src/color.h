#include <cstdint>

struct Color
{
  std::uint_fast8_t red;
  std::uint_fast8_t green;
  std::uint_fast8_t blue;
  std::uint_fast8_t alpha{ 0xFF };
};
