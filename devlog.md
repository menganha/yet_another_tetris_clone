# Devlog

Todo List

    - Introduce a cache with the next piece to be dispatched
    - Introduce the Super Rotation System. This includes wall kicks and things
      such as T-spins.
    - Introduce software key repeat.
    - Introduce shadow and hardrops.
    - Introduce score keeping.
    - User Interface

## 2021-06-02

Base gameplay loop has been developed. However the code is still not very clean.
Have to rethink the design to something less coupled. Using a "director" class
to manage the different components seems the most reasonable an clean.

Local member variable convention is not pleasant. Considering it to change from
`m_...` to append underscore at the end, i.e., `..._`


## 2021-06-11

Revamp of the whole game. After studying old tetris games noticed that for a
more fine control one needs a sensible input repeat delay: a large initial one
and then constant smaller ones. This was is possible to choose between a fine
move (tapping the button) or a quick, less precise, broad move (keeping the
button pressed). Still need to find sensible values for these parameters. I've
tried to keep the most simple I could at the expense of unnecessary but uncostly
per frame operations

Game is still missing key features, so it is far from finished. Basic one is the
game over condition. This is the next component to be implemented but
nevertheless come with the implementation of classes for font handling and
rendering.

### Delta Time 

The game engine delays are all measured in terms of frames. This approach is
much simpler to handle and for this small game witouth "real" phyisics it works
just fine.  Trying to implement a time-based delay would mean to refactor the
whole engine.
