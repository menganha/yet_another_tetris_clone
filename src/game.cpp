#include "game.h"

Game::Game()
{
    if (!Game::init()) {
        mIsRunning = true;
        mTetramino = Tetramino();
    }
}

Game::~Game()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    IMG_Quit();
    SDL_Quit();
    mWindow = nullptr;
    mRenderer = nullptr;
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

    mWindow = SDL_CreateWindow("Tetris",
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

    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cout << "SDL_image could not be initialized SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    return 0;
}

void
Game::gameLoop()
{
    while (mIsRunning) {
        handleInput();
        update();
        render();
        draw();
    }
}

void
Game::handleInput()
{
    while (SDL_PollEvent(&mEvent)) {
        if (mEvent.type == SDL_QUIT) {
            mIsRunning = false;
        } else if (mEvent.type == SDL_KEYDOWN) {
            // Select surfaces based on key press
            switch (mEvent.key.keysym.sym) {
                case SDLK_UP:
                    break;

                case SDLK_DOWN:
                    break;
            }
        }
    }
}

void
Game::update()
{
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0x00);
    SDL_RenderClear(mRenderer);
    mTetramino.update();
}

void
Game::render()
{
    mTetramino.render(mRenderer);
}

void
Game::draw()
{
    SDL_RenderPresent(mRenderer);
}
