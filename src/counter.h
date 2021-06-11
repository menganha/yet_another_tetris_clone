#ifndef COUNTER_H
#define COUNTER_H

// Helper class to generate counters for use in waiting events.
class Counter
{
public:
  Counter(int n_frames);
  bool isDone() const;
  void Stop();
  void Update();
  void Reset();

private:
  const int n_frames_;
  int counter_;
};

#endif
