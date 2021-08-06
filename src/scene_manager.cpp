#include "scene_manager.h"
#include <stdexcept>

SceneManager::SceneManager() noexcept
  : quit_game_{ false }
  , title_screen_scene_{ nullptr }
  , main_game_scene_{ nullptr }
  , current_scene_{ nullptr }
  , current_scene_type_{ SceneType::kTitleScreen }
{}

void
SceneManager::RunGame(SceneType initial_scene_type)
{
  current_scene_type_ = initial_scene_type;
  current_scene_ = GetSceneFromType(initial_scene_type);
  while (not quit_game_) {

    current_scene_->RunLoop();

    if (current_scene_->NextSceneType() == SceneType::kNoScene) {
      quit_game_ = true;
    } else {
      current_scene_ = GetSceneFromType(current_scene_->NextSceneType());
    }
  }
}

void
SceneManager::RegisterScene(Scene* scene, SceneType scene_type)
{
  Scene*& selected_scene = GetSceneFromType(scene_type);
  selected_scene = scene;
}

Scene*&
SceneManager::GetSceneFromType(SceneType scene_type)
{
  switch (scene_type) {
    case SceneType::kTitleScreen:
      return title_screen_scene_;
    case SceneType::kMainGame:
      return main_game_scene_;
    default:
      throw std::invalid_argument("Manager for scene type not implemented");
  }
}
