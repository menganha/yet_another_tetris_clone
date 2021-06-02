#include "counter.h"

Counter::Counter(int n_frames)
  : m_n_frames{ n_frames }
  , m_counter{ 0 }
{}

bool
Counter::isIdle() const
{
  return m_counter == m_n_frames;
}

void
Counter::reset()
{
  m_counter = 0;
}

void
Counter::update()
{
  if (not isIdle())
    m_counter++;
}
