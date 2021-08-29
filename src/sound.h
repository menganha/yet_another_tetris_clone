#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>
#include <filesystem>
#include <string>

class Sound
{

public:
  Sound(std::string file_name);
  ~Sound();
  void Play();

private:
  Mix_Chunk*                         chunk_; // Holds the music chung
  static const std::filesystem::path sound_assets_path_;
};

#endif
