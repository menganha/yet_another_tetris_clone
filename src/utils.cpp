#include "utils.h"
#include "counter.h"

void
utils::Wait(int n_frames, SDL_Renderer* renderer)
{
  // Wait an amount of frames and draw the same image over and over
  Counter initial_delay{ n_frames };
  initial_delay.Reset();
  while (!initial_delay.isDone()) {
    initial_delay.Update();
    SDL_RenderPresent(renderer);
  }
}
