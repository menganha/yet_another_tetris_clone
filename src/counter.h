
// Helper class to generate counters for use in waiting events.

class Counter
{
  public:
    Counter(int n_frames);
    bool isIdle() const;
    void reset();
    void update();
  private:
    const int m_n_frames;
    int m_counter;
};
