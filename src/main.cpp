#include "main_game_scene.h"
#include "scene.h"
#include "scene_maganer.h"
#include "sdl_engine.h"
#include "title_screen_scene.h"

int
main()
{
  SDLEngine engine{};
  engine.Init();
  MainGameScene    game_scene{ engine.renderer(), engine.font() };
  TitleScreenScene title_screen_scene{ engine.renderer() };
  SceneManager     scene_manager{ &title_screen_scene, &game_scene };

  scene_manager.ChangeSceneTo(SceneType::kMainGame);
}
