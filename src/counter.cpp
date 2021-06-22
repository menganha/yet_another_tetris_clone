#include "counter.h"

Counter::Counter(int n_frames)
  : n_frames_{ n_frames }
  , counter_{ n_frames }
{}

bool
Counter::isDone() const
{
  return counter_ == n_frames_;
}

void
Counter::Stop()
{
  counter_ = n_frames_;
}

void
Counter::Reset()
{
  counter_ = 0;
}

void
Counter::Update()
{
  if (!isDone()) {
    ++counter_;
  }
}
