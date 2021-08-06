#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene.h"
#include "scene_type.h"

// Manages the scenes and keeps track for all of them
class SceneManager
{
public:
  SceneManager() noexcept;
  void RunGame(SceneType initial_scene_type);
  void RegisterScene(Scene* scene, SceneType scene_type);

private:
  bool      quit_game_;
  Scene*    title_screen_scene_;
  Scene*    main_game_scene_;
  Scene*    current_scene_; // Serves as a reference to potentially run onQuit methods when changing the scene
  SceneType current_scene_type_;
  Scene*&   GetSceneFromType(SceneType scene_type);
};

#endif
