#ifndef TETROMINO_H
#define TETROMINO_H

class Grid;
#include <SDL2/SDL.h>
#include <array>

class Tetromino
{

public:
  static int const kTetrominoSize = 4;
  enum Type
  {
    T_block,
    L_block,
    J_block,
    Z_block,
    S_block,
    O_block,
    I_block,
    TotalTypes
  };
  enum RotationState // Using the same lables as in the tetris wiki
  {
    rot_0,
    rot_R,
    rot_2,
    rot_L,
    TotalRotationTypes
  };
  using Coord = std::array<SDL_Point, kTetrominoSize>;
  static Coord const kDefinition[TotalTypes]; // Tetrominos definition with respect to a local frame of reference where
                                              // the point 1,1 is the rotation center. These coordinates represent the
                                              // block coordinates of in the initial orientation of the tetromino

  // Offset Data used for the Super Rotation System
  static int const   offset_possibilities_Tetromino = 5;
  static int const   offset_possibilities_O_Tetromino = 1;
  static std::array<SDL_Point, TotalRotationTypes> const OffSetData[offset_possibilities_Tetromino];
  static std::array<SDL_Point, TotalRotationTypes> const I_Tetromino_OffSetData[offset_possibilities_Tetromino];
  static std::array<SDL_Point, TotalRotationTypes> const O_Tetromino_OffSetData[offset_possibilities_O_Tetromino];

  Tetromino(Type type, const SDL_Color color);

  void        ResetPosition();
  SDL_Color   GetColor() const;
  Coord       get_containing_cell_indices() const;
  Type        get_type() const;
  int         get_offset_possibilities() const;
  void        Move(int delta_x, int delta_y);
  bool        Collides(const Grid& grid) const;
  bool        Lands(const Grid& grid) const;
  void        Rotate(bool direction, int offset_case);
  void        CacheCoordinates();
  void        RestoreFromCache();
  void        Render(SDL_Renderer* renderer) const;
  void        RenderIntitialStateAt(SDL_Renderer* renderer, int const pos_x, int const pos_y) const;
  static void RenderBlock(SDL_Renderer* renderer, int const pos_x, int const pos_y, SDL_Color const color);

private:
  SDL_Color const color_;
  Type const      type_;
  SDL_Point const initial_frame_coord_;
  SDL_Point       frame_coord_;
  SDL_Point       cache_frame_coord_;
  Coord const     initial_rel_coord_;
  Coord           rel_coord_;
  Coord           cache_rel_coord_;
  Coord           abs_coord_;
  void            UpdateAbsCoord();
  SDL_Point       AdjustedInitialPosition(int pos_x, int pos_y);
  int             rotation_index_;
  int             offset_possibilities_;
  int             cache_rotation_index_;
  int             GetRotationState(int rotation_index);
};

#endif
