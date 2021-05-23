#include "game.h"

Game::Game()
{
  if (!Game::init()) {
    mIsRunning = true;
    mTetromino = mTetrominoManager.get_next_tetromino();
    mGrid = new Grid{};
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
    std::cout << "SDL could not initialize! SDL Error " << SDL_GetError()
              << std::endl;
    return -1;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
  }

  mWindow = SDL_CreateWindow("Tetris",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             constant::SCREEN_WIDTH,
                             constant::SCREEN_HEIGHT,
                             SDL_WINDOW_SHOWN);
  if (mWindow == nullptr) {
    std::cout << "Window could not be created! SDL Error: " << SDL_GetError()
              << std::endl;
    return -1;
  }

  mRenderer = SDL_CreateRenderer(
    mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (mRenderer == nullptr) {
    std::cout << "Renderer could not be created SDL Error: " << SDL_GetError()
              << std::endl;
    return -1;
  }

  SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

  if (!IMG_Init(IMG_INIT_PNG)) {
    std::cout << "SDL_image could not be initialized SDL Error: "
              << SDL_GetError() << std::endl;
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
  SDL_SetRenderDrawColor(mRenderer,
                         constant::BLACK.red,
                         constant::BLACK.green,
                         constant::BLACK.blue,
                         constant::BLACK.alpha);
  SDL_RenderClear(mRenderer);
  mController.update();
  mTetromino->update(mController);
  bool tetromino_has_landed = mGrid->update(mTetromino);

  if (tetromino_has_landed) {
    mTetromino = mTetrominoManager.get_next_tetromino();
    mTetromino->resetPos();
  }

  if (mController.mQuit) {
    mIsRunning = false;
  }
}

void
Game::render()
{
  mGrid->render(mRenderer);
  mTetromino->render(mRenderer);
}

void
Game::draw()
{
  SDL_RenderPresent(mRenderer);
}
