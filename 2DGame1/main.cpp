#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Game game;

    if (!game.Initialize()) {
        return -1;
    }

    game.Run();

    return 0;
}