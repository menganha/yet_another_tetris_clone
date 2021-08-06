#ifndef SCENE_H
#define SCENE_H

#include "scene_type.h"

// Abstract interface to specify all game scenes
class Scene
{
public:
  virtual void            RunLoop() = 0;
  virtual SceneType NextSceneType() const = 0;
};

#endif
