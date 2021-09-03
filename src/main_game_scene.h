#ifndef MAIN_GAME_SCENE_H
#define MAIN_GAME_SCENE_H

class Tetromino;
#include "counter.h"
#include "grid.h"
#include "input.h"
#include "scene.h"
#include "scene_type.h"
#include "tetromino_manager.h"
#include "user_interface.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "sound.h"

class MainGameScene : public Scene
{
public:
  MainGameScene(SDL_Renderer* renderer, TTF_Font* font);
  void      RunLoop();
  SceneType NextSceneType() const;

private:
  SDL_Renderer*    renderer_;
  bool             game_over_;
  bool             is_running_;
  int              score_;
  int              level_;
  SceneType        next_scene_type_;
  Input            input_;
  UserInterface    ui;
  TetrominoManager tetromino_manager_;
  Tetromino*       pTetromino_;
  Grid             grid_;
  Counter          lock_delay_; // Frame until the landed piece locks in position
  Counter          fall_delay_; // Amount of frames to wait till the tetromino falls by one unit
  Sound            sound_block_lands_;
  Sound            sound_clear_rows_;

  void             Update();
  void             Render();
  void             Draw();
  int              ClearedRowsToScore(int const cleared_rows) const;
  void             HandleGameOver();
  void             Restart();
};

#endif
