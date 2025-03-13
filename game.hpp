#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
using namespace std;

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int wdth, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

    SDL_Renderer *renderer;
    SDL_Window *window;

private:
    // main variables
    bool isRunning;
};


#endif