#include "controller.h"

Controller::Controller()
  : mUP{ false }
  , mDOWN{ false }
  , mLEFT{ false }
  , mRIGHT{ false }
  , mACTION{ false }
  , mPAUSE{ false }
{}

Controller::~Controller() {}

void
Controller::update()
{
    Controller::reset();
    while (SDL_PollEvent(&mEvent)) {
        switch (mEvent.type) {
            case SDL_QUIT:
                mQuit = true;
                break;
            case SDL_KEYDOWN:
                if (mEvent.key.repeat == 0) {
                    switch (mEvent.key.keysym.sym) {
                        case SDLK_RIGHT:
                            mRIGHT = true;
                            break;
                        case SDLK_LEFT:
                            mLEFT = true;
                            break;
                        case SDLK_DOWN:
                            mDOWN = true;
                            break;
                        case SDLK_UP:
                            mUP = true;
                            break;
                        case SDLK_x:
                            mACTION = true;
                            break;
                        case SDLK_RETURN:
                            mPAUSE = true;
                            break;
                    }
                    break;
                } else {
                    break;
                }
        }
    }
}

void
Controller::reset()
{
    mUP = false;
    mDOWN = false;
    mLEFT = false;
    mRIGHT = false;
    mACTION = false;
    mPAUSE = false;
}
