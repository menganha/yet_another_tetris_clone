#include "main_game_scene.h"
#include "scene.h"
#include "scene_manager.h"
#include "sdl_engine.h"
#include "title_screen_scene.h"

int
main()
{
  SDLEngine engine{};
  engine.Init();
  SceneManager     scene_manager;
  MainGameScene    game_scene{ engine.renderer(), engine.font() };
  TitleScreenScene title_screen_scene{ engine.renderer(), engine.font() };

  scene_manager.RegisterScene(&game_scene, SceneType::kMainGame);
  scene_manager.RegisterScene(&title_screen_scene, SceneType::kTitleScreen);

  scene_manager.RunGame(SceneType::kTitleScreen);
}
