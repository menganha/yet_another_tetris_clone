# Devlog

Todo List

    - [X] Introduce a cache with the next piece to be dispatched
    - [ ] Introduce the Super Rotation System. This includes wall kicks and things
      such as T-spins.
    - [ ] Lose condition.
    - [X] Introduce software key repeat.
    - [ ] Introduce shadow and hardrops.
    - [ ] Introduce score keeping.
    - [ ] User Interface. Includes starting game screen, exiting game
      confirmation pop-ups.

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


## 2021-06-25

Implemented finally the in-game key repeat/delay emulation. Cleaned up a bit and
encapsulated more of the code. Apart from the super rotation system, game
mechanics are all implemented and tested. No more bugs!

Now I'm introducing text data structures to the game which will form the base for
the simple UI system. This requires to use yet another feature of the SDL lib,
namely Textures, which I'm now studying. It may require some iterations before I
get it right and clean.

Leaving super rotation system for later. It is simpler to implement but I want
to focus now in having a full "game" experience before polishing details.


