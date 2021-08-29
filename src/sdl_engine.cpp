#include "sdl_engine.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <stdexcept>
#include <string>

SDLEngine::SDLEngine()
  : renderer_{ nullptr }
  , font_{ nullptr }
  , window_{ nullptr }
{}

SDLEngine::~SDLEngine()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  window_ = nullptr;
  renderer_ = nullptr;
  TTF_Quit();
  Mix_Quit();
  SDL_Quit();
}

void
SDLEngine::Init()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::string err_msg = "SDL could not initialize! SDL Error: ";
    throw std::runtime_error(err_msg + SDL_GetError());
  }

  if (TTF_Init() < 0) {
    std::string err_msg = "Could not initialize TTF extension! SDL Error: ";
    throw std::runtime_error(err_msg + TTF_GetError());
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
  }

  window_ = SDL_CreateWindow("Yet Another Tetris Clone",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             constant::kScreenWidth,
                             constant::kScreenHeight,
                             SDL_WINDOW_SHOWN);
  if (window_ == nullptr) {
    std::string err_msg = "Window could not be created! SDL Error: ";
    throw std::runtime_error(err_msg + SDL_GetError());
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == nullptr) {
    std::string err_msg = "Renderer could not be created SDL Error: ";
    throw std::runtime_error(err_msg + SDL_GetError());
  }

  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
  
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::string err_msg = "Could not initialize SDL_mixer extension! SDL Error: ";
    throw std::runtime_error(err_msg + Mix_GetError());
  }

  font_ = TTF_OpenFont("font/PressStart2P.ttf", 20);
  if (font_ == nullptr) {
    std::string err_msg = "Could not load font! SDL Error: ";
    throw std::runtime_error(err_msg + TTF_GetError());
  }
}
