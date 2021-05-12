#include "game.h"

int
main(int argc, char* args[])
{
    Game gameApp = Game();
    gameApp.gameLoop();

    return 0;
}
