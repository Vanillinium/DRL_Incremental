#ifndef game_hpp
#define game_hpp

#include <SDL2/SDl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

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

    // game variables
    bool ClickedInBox = false;
    int money = 0; // currency
    SDL_Point mousePosition;

private:
    // main variables
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

};


#endif