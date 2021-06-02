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


