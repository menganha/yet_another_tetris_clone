#include "main_game_scene.h"
#include "color.h"
#include "constant.h"

MainGameScene::MainGameScene(SDL_Renderer* renderer, TTF_Font* font)
  : renderer_{ renderer }
  , game_over_{ false }
  , is_running_{ true }
  , score_{ 0 }
  , level_{ 1 }
  , next_scene_type_{ SceneType::kNoScene }
  , input_{ 3, 10, 5 }
  , ui{ renderer, font }
  , tetromino_manager_{}
  , pTetromino_{ tetromino_manager_.GetNextTetromino() }
  , lock_delay_{ 30 }
  , fall_delay_{ 50 }
{
  lock_delay_.Reset();
  fall_delay_.Reset();
}

void
MainGameScene::Restart()
{
  // TODO: RESTART should be a private method and should be run always on exit!
  game_over_ = false;
  is_running_ = true;
  lock_delay_.Reset();
  fall_delay_.Reset();
  score_ = 0;
  level_ = 1;
  pTetromino_ = tetromino_manager_.GetNextTetromino();
  pTetromino_->ResetPosition();
  grid_.ClearGrid();
}

void
MainGameScene::RunLoop()
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

SceneType
MainGameScene::NextSceneType() const
{
  return next_scene_type_;
}

void
MainGameScene::HandleGameOver()
{
  // Set all cells row by row: grid_.set_cell()
  // Release until all cells have been filled then show Game Over message.
  // reset input
  if (input_.Quit()) {
    is_running_ = false;
    next_scene_type_ = SceneType::kNoScene;
  }
  if (input_.Action()) {
    Restart();
  }
}

void
MainGameScene::Update()
{

  if (input_.Quit()) {
    is_running_ = false;
    next_scene_type_ = SceneType::kNoScene;
  }

  // Save Coordinates and update the delay counter
  pTetromino_->CacheCoordinates();
  fall_delay_.Update();

  // Handle all input
  // Let tetromino fall if the frame delay is completed or doing a soft drop and no tetromino is below it
  if ((fall_delay_.isDone() or input_.Down()) and not pTetromino_->Lands(grid_)) {
    pTetromino_->Move(0, constant::kCellSize);
    fall_delay_.Reset();
    return;
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

  // Check if tetromino is below current piece and starts the lock counter
  if (pTetromino_->Lands(grid_)) {
    lock_delay_.Update();
  } else {
    lock_delay_.Reset();
  }

  // Wait lock_delay to lock the pieces onto the grid
  if (lock_delay_.isDone()) {
    lock_delay_.Reset();
    for (SDL_Point indices : pTetromino_->get_containing_cell_indices()) {
      grid_.set_cell(indices.x, indices.y, true, pTetromino_->GetColor());
    }
    // Update grid and counts cleared rows
    grid_.Update();
    if (grid_.get_completed_rows() != 0) {
      score_ += ClearedRowsToScore(grid_.get_completed_rows());
      ui.UpdateScore(score_);
    }
    // Get Next Tetromino
    pTetromino_ = tetromino_manager_.GetNextTetromino();
    pTetromino_->ResetPosition();
    fall_delay_.Reset();

    // Check if tetromino is on top, signaling game over
    if (pTetromino_->Collides(grid_)) {
      game_over_ = true;
    }
  }
}

void
MainGameScene::Render()
{
  SDL_SetRenderDrawColor(renderer_, colors::BLACK.r, colors::BLACK.g, colors::BLACK.b, colors::BLACK.a);
  SDL_RenderClear(renderer_);
  grid_.Render(renderer_);
  pTetromino_->Render(renderer_);
  tetromino_manager_.RenderCachedTetromino(renderer_);
  ui.Render(game_over_);
}

void
MainGameScene::Draw()
{
  SDL_RenderPresent(renderer_);
}

int
MainGameScene::ClearedRowsToScore(int const cleared_rows) const
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
