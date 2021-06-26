#include "game.h"

Game::Game()
  : game_over_{ false }
  , is_running_{ false }
  , score_{ 0 }
  , level_{ 1 }
  , input_{ 3, 10, 5 }
  , window_{ nullptr }
  , renderer_{ nullptr }
  , pTetromino_{ nullptr }
  , lock_delay_{ 30 }
  , fall_delay_{ 50 }
  , next_piece_text_{ "NEXT", colors::WHITE, constant::kNextTextPosX, constant::kNextTextPosY }
  , score_text_{ "SCORE", colors::WHITE, constant::kScoreTextPosX, constant::kScoreTextPosY }
  , score_value_text_{ "000000", colors::WHITE, constant::kScoreValueTextPosX, constant::kScoreValueTextPosY }
  , level_text_{ "LEVEL", colors::WHITE, constant::kLevelTextPosX, constant::kLevelTextPosY }
  , level_value_text_{ "1", colors::WHITE, constant::kLevelValueTextPosX, constant::kLevelValueTextPosY }
  , game_over_text_{ "GAME OVER", colors::WHITE, constant::kGameOverTextPosX, constant::kGameOverTextPosY }
{
  if (!Game::Init()) {
    is_running_ = true;
    pTetromino_ = mTetrominoManager.GetNextTetromino();
    lock_delay_.Reset();
    fall_delay_.Reset();
    next_piece_text_.Load(renderer_);
    score_text_.Load(renderer_);
    score_value_text_.Load(renderer_);
    level_text_.Load(renderer_);
    level_value_text_.Load(renderer_);
    game_over_text_.Load(renderer_);
  }
}

Game::~Game()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  window_ = nullptr;
  renderer_ = nullptr;
  TTF_Quit();
  SDL_Quit();
}

int
Game::Init()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL Error " << SDL_GetError() << std::endl;
    return -1;
  }

  if (TTF_Init() < 0) {
    std::cout << "Could not initialize TTF extension! SDL Error " << TTF_GetError() << std::endl;
    return -1;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
  }

  window_ = SDL_CreateWindow("Yet Another Tetris Clone",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             constant::kScreenWidth,
                             constant::kScreenSize,
                             SDL_WINDOW_SHOWN);
  if (window_ == nullptr) {
    std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == nullptr) {
    std::cout << "Renderer could not be created SDL Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);

  return 0;
}

void
Game::RunLoop()
{
  while (is_running_) {
    input_.Update();
    if (not game_over_) {
      Update();
    } else {
      HandleGameOver();
    }
    Render();
    Draw();
  }
}

void
Game::HandleGameOver()
{
  // Set all cell row by row: grid_.set_cell()
  // Release until all cells have been filled
  // then show Game Over message
  // reset input
  if (input_.Quit()) {
    is_running_ = false;
  }
}

void
Game::Update()
{
  fall_delay_.Update();

  if (input_.Quit()) {
    is_running_ = false;
  }

  // Check if is in a position for landing
  pTetromino_->CacheCoordinates();
  bool in_landing_position = pTetromino_->Lands(grid_);

  if (in_landing_position) {
    lock_delay_.Update();
  } else {
    lock_delay_.Reset();
  }

  // Let tetromino fall if the frame delay is completed
  if ((fall_delay_.isDone() or input_.Down()) and not in_landing_position) {
    pTetromino_->Move(0, constant::kCellSize);
    fall_delay_.Reset();
  }
  if (input_.Left()) {
    pTetromino_->Move(-constant::kCellSize, 0);
  }
  if (input_.Right()) {
    pTetromino_->Move(constant::kCellSize, 0);
  }
  if (pTetromino_->Collides(grid_)) {
    pTetromino_->RestoreFromCache();
  }
  if (input_.Action()) {
    pTetromino_->CacheCoordinates();
    pTetromino_->Rotate();
    if (pTetromino_->Collides(grid_)) {
      pTetromino_->RestoreFromCache();
    }
  }

  // Wait lock_delay to lock the pieces onto the grid
  if (lock_delay_.isDone()) {
    for (SDL_Point indices : pTetromino_->get_containing_cell_indices()) {
      grid_.set_cell(indices.x, indices.y, true, pTetromino_->GetColor());
    }
    pTetromino_ = mTetrominoManager.GetNextTetromino();
    pTetromino_->ResetPosition();
    fall_delay_.Reset();

    // Check if tetromino is on top, signaling game over
    if (pTetromino_->Collides(grid_)) {
      game_over_ = true;
      return;
    }
  }

  // Update grid and counts cleared rows
  grid_.Update();
  if (grid_.get_completed_rows() != 0) {
    score_ += ClearedRowsToScore(grid_.get_completed_rows());
    auto not_padded = std::to_string(score_);
    score_value_text_.ChangeString(renderer_, std::string(6 - not_padded.length(), '0') + not_padded);
  }
}

void
Game::Render()
{
  SDL_SetRenderDrawColor(renderer_, colors::BLACK.r, colors::BLACK.g, colors::BLACK.b, colors::BLACK.a);
  SDL_RenderClear(renderer_);
  grid_.Render(renderer_);
  pTetromino_->Render(renderer_);
  mTetrominoManager.RenderCachedTetromino(renderer_);
  next_piece_text_.Render(renderer_);
  score_text_.Render(renderer_);
  score_value_text_.Render(renderer_);
  level_text_.Render(renderer_);
  level_value_text_.Render(renderer_);
  if (game_over_) {
    game_over_text_.Render(renderer_);
  }
}

void
Game::Draw()
{
  SDL_RenderPresent(renderer_);
}

int
Game::ClearedRowsToScore(int const cleared_rows) const
{
  if (cleared_rows == 4) {
    return 800 * level_;
  } else if (cleared_rows == 3) {
    return 500 * level_;
  } else if (cleared_rows == 2) {
    return 300 * level_;
  } else { // just one row
    return 100 * level_;
  }
}
