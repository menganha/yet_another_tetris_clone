#include "input.h"

Input::Input(int down_key_repeat, int horizontal_key_delay, int horizontal_key_repeat)
  : controller_{
    { 0, down_key_repeat},                           // up
    { 0, down_key_repeat},                           // down
    { horizontal_key_delay, horizontal_key_repeat }, // left
    { horizontal_key_delay, horizontal_key_repeat }, // right
    { 0, 0, false },                                 // action
    { 0, 0, false },                                 // pause
    { 0, 0, false },                                 // quit
  }
{}

Input::~Input() {}

void
Input::Update()
{
  while (SDL_PollEvent(&event_)) {
    if (event_.type == SDL_QUIT) {
      // if closing window or os receiving quiting signal then
      // interpret as pressing the quit button
      controller_.quit.Update();
    }
  }
  const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
  if (currentKeyStates[SDL_SCANCODE_UP]) {
    controller_.up.Update();
  } else {
    controller_.up.Reset();
  }
  if (currentKeyStates[SDL_SCANCODE_DOWN]) {
    controller_.down.Update();
  } else {
    controller_.down.Reset();
  }
  if (currentKeyStates[SDL_SCANCODE_LEFT]) {
    controller_.left.Update();
  } else {
    controller_.left.Reset();
  }
  if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
    controller_.right.Update();
  } else {
    controller_.right.Reset();
  }
  if (currentKeyStates[SDL_SCANCODE_X]) {
    controller_.action.Update();
  } else {
    controller_.action.Reset();
  }
  if (currentKeyStates[SDL_SCANCODE_RETURN]) {
    controller_.pause.Update();
  } else {
    controller_.pause.Reset();
  }
}

Button::Button(int repeat_delay, int repeat_rate, bool repeat_t)
  : state{ false }
  , is_first_press{ true }
  , repeat{ repeat_t }
  , counter_delay{ repeat_delay }
  , counter_repeat{ repeat_rate }
{}

void
Button::Update()
{
  state = false;
  if (is_first_press) {
    counter_delay.Reset();
    is_first_press = false;
    state = true;
  } else if (repeat && counter_delay.isDone() && counter_repeat.isDone()) {
    counter_repeat.Reset();
    state = true;
  }
  counter_delay.Update();
  counter_repeat.Update();
}

void
Button::Reset()
{
  state = false;
  is_first_press = true;
}

bool
Button::GetState() const
{
  return state;
}
