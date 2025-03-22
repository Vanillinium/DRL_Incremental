#include "game.hpp"

Game *game = nullptr;
const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[]){
    
    const int maxFPS = 60;
    const int frameDelay = 1000 / maxFPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
    
    while(game->running()){

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}  