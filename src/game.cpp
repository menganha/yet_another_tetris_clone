#include "game.h"

Game::Game()
  : input_{ 3, 10, 5 }
  , lock_delay_{ 30 }
  , fall_delay_{ 50 }
{
  if (!Game::init()) {
    is_running_ = true;
    in_landing_position = false;
    pTetromino_ = mTetrominoManager.GetNextTetromino();
    lock_delay_.Reset();
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

  SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);

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

  // Check if is in a position for landing
  Tetromino::ElementCoord tmp_coord = pTetromino_->get_coord();
  in_landing_position = pTetromino_->lands(grid_);

  if (in_landing_position) {
    lock_delay_.Update();
  } else {
    lock_delay_.Reset();
  }

  // Let tetromino fall if the frame delay is completed
  if ((fall_delay_.isDone() || input_.Down()) && not in_landing_position) {
    pTetromino_->move(0, constant::CELL_SIZE);
    fall_delay_.Reset();
  }

  // Wait lock_delay to lock the pieces onto the grid
  if (lock_delay_.isDone()) {
    for (SDL_Point indices : pTetromino_->get_containing_cell_indices()) {
      grid_.set_cell(indices.x, indices.y, true, pTetromino_->get_color());
    }
    pTetromino_ = mTetrominoManager.GetNextTetromino();
    pTetromino_->reset_position();
    fall_delay_.Reset();
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
    // BUG: Funnyu thing whith the Z, S and T pieces. When not being able to rotate, following rotations are
    // bigger
    pTetromino_->rotate();
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
  SDL_SetRenderDrawColor(mRenderer, colors::BLACK.red, colors::BLACK.green, colors::BLACK.blue, colors::BLACK.alpha);
  SDL_RenderClear(mRenderer);
  grid_.render(mRenderer);
  pTetromino_->render(mRenderer);
  // TODO: ADD here the render of the cached piece
}

void
Game::draw()
{
  SDL_RenderPresent(mRenderer);
}
