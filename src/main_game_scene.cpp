#include "main_game_scene.h"
#include "color.h"
#include "constant.h"
#include "utils.h"

MainGameScene::MainGameScene(SDL_Renderer* renderer, TTF_Font* font)
  : renderer_{ renderer }
  , game_over_{ false }
  , pause_{ false }
  , is_running_{ true }
  , restart_{ false }
  , score_{ 0 }
  , total_cleared_lines_{ 0 }
  , level_{ 0 }
  , next_scene_type_{ SceneType::kNoScene }
  , input_{ 2, 12, 4 }
  , ui{ renderer, font }
  , tetromino_manager_{}
  , pTetromino_{ tetromino_manager_.GetNextTetromino() }
  , lock_delay_{ 30 }
  , fall_delay_{ 48 }
  , sound_block_lands_{ "block_lands.wav" }
  , sound_clear_rows_{ "clear_rows.wav" }
  , sound_block_moves_{ "move_tetromino.wav" }
  , sound_block_rotates_{ "rotate.wav" }
  , in_game_menu_{ renderer, font }
{
  lock_delay_.Reset();
  fall_delay_.Reset();
}

void
MainGameScene::SetToDefault()
{
  // Sets all variables to the default for starting a new game afresh
  game_over_ = false;
  pause_ = false;
  restart_ = false;
  is_running_ = true;
  total_cleared_lines_ = 0;
  score_ = 0;
  level_ = 0;
  ui.UpdateLevel(level_);
  ui.UpdateScore(score_);
  fall_delay_.ChangeNumberOfFrames(48);
  pTetromino_ = tetromino_manager_.GetNextTetromino();
  pTetromino_->ResetPosition();
  lock_delay_.Reset();
  fall_delay_.Reset();
  grid_.ClearGrid();
  input_.Reset();
  in_game_menu_.current_selected_item = 0;
  utils::Wait(10, renderer_);
}

void
MainGameScene::RunLoop()
{
  while (is_running_) {
    input_.Update();

    if (input_.Quit()) {
      is_running_ = false;
      next_scene_type_ = SceneType::kNoScene;
    } else if (input_.Pause()) {
      pause_ = not pause_;
    }

    if (game_over_ or pause_) {
      UpdatePauseScreen();
    } else {
      Update();
    }

    Render();
    Draw();

    if (restart_) {
      SetToDefault();
    }
  }
  SetToDefault();
}

SceneType
MainGameScene::NextSceneType() const
{
  return next_scene_type_;
}

void
MainGameScene::UpdatePauseScreen()
{
  in_game_menu_.Update();

  if (input_.Up()) {
    in_game_menu_.current_selected_item -= 1;
    in_game_menu_.current_selected_item = std::max(in_game_menu_.current_selected_item, 0);
  } else if (input_.Down()) {
    in_game_menu_.current_selected_item += 1;
    in_game_menu_.current_selected_item = std::min(in_game_menu_.current_selected_item, 1);
  }

  if (in_game_menu_.current_selected_item == 0) {
    if (game_over_ and (input_.A())) {
      restart_ = true;
    } else if (pause_ and (input_.A())) {
      pause_ = false;
    }
  } else if (in_game_menu_.current_selected_item == 1) {
    if (input_.A()) {
      is_running_ = false;
      /* restart_ = true; */
      next_scene_type_ = SceneType::kTitleScreen;
    }
  }
}

void
MainGameScene::Update()
{
  // Handle all input

  // Save Coordinates and update the delay counter
  pTetromino_->CacheCoordinates();

  bool play_move_sound = false;
  if (input_.Left()) {
    pTetromino_->Move(-constant::kCellSize, 0);
    play_move_sound = true;
  }
  if (input_.Right()) {
    pTetromino_->Move(constant::kCellSize, 0);
    play_move_sound = true;
  }
  if (pTetromino_->Collides(grid_)) {
    pTetromino_->RestoreFromCache();
    play_move_sound = false;
  }
  if (play_move_sound) {
    sound_block_moves_.Play();
  }

  if (input_.A() or input_.B()) {
    pTetromino_->CacheCoordinates();
    for (int idx = 0; idx < pTetromino_->get_offset_possibilities(); ++idx) {
      pTetromino_->Rotate(input_.A(), idx);
      if (pTetromino_->Collides(grid_)) {
        pTetromino_->RestoreFromCache();
      } else {
        sound_block_rotates_.Play();
        break;
      }
    }
  }

  // Let tetromino fall if the frame delay is completed or doing a soft drop and no tetromino is below it
  fall_delay_.Update();
  if ((fall_delay_.isDone() or input_.Down()) and not pTetromino_->Lands(grid_)) {
    pTetromino_->Move(0, constant::kCellSize);
    fall_delay_.Reset();
    return;
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
    sound_block_lands_.Play();
    // Update grid and counts cleared rows
    grid_.Update();
    if (grid_.get_completed_rows() != 0) {
      sound_clear_rows_.Play();
      HandleScoring(grid_.get_completed_rows());
    }
    // Get Next Tetromino
    pTetromino_ = tetromino_manager_.GetNextTetromino();
    pTetromino_->ResetPosition();
    fall_delay_.Reset();

    // Check if tetromino is on top, signaling game over
    if (pTetromino_->Collides(grid_)) {
      game_over_ = true;
    }
    return;
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
  ui.Render();
  if (game_over_ or pause_) {
    in_game_menu_.Render(game_over_);
  }
}

void
MainGameScene::Draw()
{
  SDL_RenderPresent(renderer_);
}

void
MainGameScene::HandleScoring(int const cleared_rows)
{
  // Update Score
  if (cleared_rows == 4) {
    score_ += 1200 * (level_ + 1);
  } else if (cleared_rows == 3) {
    score_ += 300 * (level_ + 1);
  } else if (cleared_rows == 2) {
    score_ += 100 * (level_ + 1);
  } else { // just one row
    score_ += 40 * (level_ + 1);
  }
  ui.UpdateScore(score_);

  // Update Level
  total_cleared_lines_ += cleared_rows;
  if (total_cleared_lines_ / 10 >= level_ + 1) {
    level_ += 1;
    int n_frames_fall_delay = std::max(48 - 5 * level_, 5);
    fall_delay_.ChangeNumberOfFrames(n_frames_fall_delay);
    ui.UpdateLevel(level_);
  }
}
