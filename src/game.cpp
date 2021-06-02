#include "game.h"

Game::Game()
{
  if (!Game::init()) {
    mIsRunning = true;
    mTetromino = mTetrominoManager.get_next_tetromino();
  }
}

Game::~Game()
{
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  mWindow = nullptr;
  mRenderer = nullptr;
  IMG_Quit();
  SDL_Quit();
}

int
Game::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL Error " << SDL_GetError() << std::endl;
    return -1;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
  }

  mWindow = SDL_CreateWindow("Yet Another Tetris Clone",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             constant::SCREEN_WIDTH,
                             constant::SCREEN_HEIGHT,
                             SDL_WINDOW_SHOWN);
  if (mWindow == nullptr) {
    std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (mRenderer == nullptr) {
    std::cout << "Renderer could not be created SDL Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  return 0;
}

void
Game::gameLoop()
{
  while (mIsRunning) {
    update();
    render();
    draw();
  }
}

void
Game::update()
{
  SDL_SetRenderDrawColor(
    mRenderer, colors::BLACK.red, colors::BLACK.green, colors::BLACK.blue, colors::BLACK.alpha);
  SDL_RenderClear(mRenderer);
  mController.update();
  mGrid.update();
  mTetromino->update(mController, mGrid);

  if (mTetromino->has_landed()) {
    mTetromino = mTetrominoManager.get_next_tetromino();
    mTetromino->reset_position();
  }

  if (mController.mQuit) {
    mIsRunning = false;
  }
}

void
Game::render()
{
  mGrid.render(mRenderer);
  mTetromino->render(mRenderer);
}

void
Game::draw()
{
  SDL_RenderPresent(mRenderer);
}
