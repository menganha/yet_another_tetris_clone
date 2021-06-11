#include "game.h"

Game::Game()
  : input_{ 3, 10, 5}
{
  if (!Game::init()) {
    is_running_ = true;
    tetromino_landed_ = false;
    pTetromino_ = mTetrominoManager.get_next_tetromino();
    fall_delay_.Reset();
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

  mWindow = SDL_CreateWindow("Yet Another Tetris Clone",
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

  return 0;
}

void
Game::gameLoop()
{
  while (is_running_) {
    update();
    render();
    draw();
  }
}

void
Game::update()
{
  input_.Update();
  grid_.update();
  fall_delay_.Update();

  // Let tetromino fall if the frame delay is completed
  Tetromino::ElementCoord tmp_coord = pTetromino_->get_coord();
  if ((fall_delay_.isDone() || input_.Down()) && not tetromino_landed_) {
    pTetromino_->move(0, constant::CELL_SIZE);
    if (pTetromino_->lands(grid_)) {
      pTetromino_->set_coord(tmp_coord);
      tetromino_landed_ = true;
      lock_delay_.Reset();
    } else {
      fall_delay_.Reset();
    }
  }

  // Wait lock_delay to lock the pieces onto the grid
  if (tetromino_landed_) {
    lock_delay_.Update();
    if (lock_delay_.isDone()) {
      for (SDL_Point indices : pTetromino_->get_containing_cell_indices()) {
        grid_.set_cell(indices.x, indices.y, true, pTetromino_->get_color());
      }
      pTetromino_ = mTetrominoManager.get_next_tetromino();
      pTetromino_->reset_position();
      fall_delay_.Reset();
      tetromino_landed_ = false;
    }
  }

  // Move tetromino according to the input. Reset position if it collides
  tmp_coord = pTetromino_->get_coord();
  int relative = false;
  if (input_.Left()) {
    pTetromino_->move(-constant::CELL_SIZE, 0);
  }
  if (input_.Right()) {
    pTetromino_->move(constant::CELL_SIZE, 0);
  }
  if (input_.Action()) {
    pTetromino_->rotate();
    // BUG: Funny rotation once one rotation move was denied
    relative = true;
  }

  if (pTetromino_->collides(grid_)) {
    pTetromino_->set_coord(tmp_coord, relative);
  }

  if (input_.Quit()) {
    is_running_ = false;
  }
}

void
Game::render()
{
  SDL_SetRenderDrawColor(mRenderer,
                         colors::BLACK.red,
                         colors::BLACK.green,
                         colors::BLACK.blue,
                         colors::BLACK.alpha);
  SDL_RenderClear(mRenderer);
  grid_.render(mRenderer);
  pTetromino_->render(mRenderer);
}

void
Game::draw()
{
  SDL_RenderPresent(mRenderer);
}
