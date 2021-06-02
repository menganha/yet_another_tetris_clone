#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <SDL2/SDL.h>

class Controller
{
  public:
    Controller();
    ~Controller();
    void update();
    bool noAction() const;
    bool mUP;
    bool mDOWN;
    bool mLEFT;
    bool mRIGHT;
    bool mACTION;
    bool mPAUSE;
    bool mQuit;

  private:
    SDL_Event mEvent;
    void reset();
};

#endif /* ifndef CONTROLLER_HH */
