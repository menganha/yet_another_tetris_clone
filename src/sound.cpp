#include "sound.h"

std::filesystem::path const Sound::sound_assets_path_{ "../sounds" };

Sound::Sound(std::string file_name)
  : chunk_{ Mix_LoadWAV((sound_assets_path_ / file_name).c_str()) }
{}

Sound::~Sound()
{
  Mix_FreeChunk(chunk_);
}

void
Sound::Play()
{
  Mix_PlayChannel(-1, chunk_, 0);
}
