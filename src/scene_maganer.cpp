#include "scene_maganer.h"

SceneManager::SceneManager(Scene* title_screen_scene, Scene* main_game_scene)
{
  title_screen_scene_ = title_screen_scene;
  main_game_scene_ = main_game_scene;
}

void
SceneManager::ChangeSceneTo(SceneType scene_type)
{
  current_scene_ = GetSceneFromType(scene_type);
  current_scene_->RunLoop();
}

Scene*
SceneManager::GetSceneFromType(SceneType scene_type)
{

  switch (scene_type) {
    case SceneType::kTitleScreen:
      return title_screen_scene_;
    case SceneType::kMainGame:
      return main_game_scene_;
    default:
      return nullptr;
  }
}
