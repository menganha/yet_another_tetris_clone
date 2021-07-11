#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "counter.h"
#include <SDL2/SDL.h>

// Input classses for keyboard and buttons which emulate the delay and repeat
// on input when leaving a key pressed.

// Button class represents an abstract single button which can optionally send
// additionally press events after a certain numbers of frames while being
// pressed
//
// repeat_delay : the initial delay before the keys start to repeat
// repeat_rate  : the delay between consecutive key repeats
// repeat    : false if it is a simple button with no repeat capability

class Button
{
public:
  Button(int repeat_delay, int repeat_rate, bool repeat_t = true);
  void Reset();
  void Update();
  bool GetState() const;

private:
  bool       state;
  bool       is_first_press;
  const bool repeat;
  Counter    counter_delay;
  Counter    counter_repeat;
};

// Input class manages all the buttons and interacts with the event queue

class Input
{
public:
  Input(int down_key_repeat, int horizontal_key_delay, int horizontal_key_repeat);
  ~Input();

  void        Update();
  inline bool Up() const { return controller_.up.GetState(); };
  inline bool Down() const { return controller_.down.GetState(); };
  inline bool Left() const { return controller_.left.GetState(); };
  inline bool Right() const { return controller_.right.GetState(); };
  inline bool Action() const { return controller_.action.GetState(); };
  inline bool Quit() const { return controller_.quit.GetState(); };

private:
  struct Controller
  {
    Button up;
    Button down;
    Button left;
    Button right;
    Button action;
    Button pause;
    Button quit;
  } controller_;
  SDL_Event event_;
};

#endif
