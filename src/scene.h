#ifndef SCENE_H
#define SCENE_H

// Abstract interface to specify all game scenes
class Scene
{
public:
  virtual void RunLoop() = 0;
};

#endif
