#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene.h"

// Type to identify the scenes
enum class SceneType
{
  kTitleScreen,
  kMainGame,
};

// Manages the scenes and keeps track for all of them
class SceneManager
{
public:
  SceneManager(Scene* title_scene, Scene* main_game_scene);
  void   ChangeSceneTo(SceneType scene_type);

private:
  Scene* title_screen_scene_;
  Scene* main_game_scene_;
  Scene* current_scene_; // Serves as a reference to potentially run onQuit methods when changing the scene
  Scene* GetSceneFromType(SceneType scene_type);
};

#endif
