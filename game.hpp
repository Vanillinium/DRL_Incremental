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
    
    // MAIN GAME COMPOMENTS
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();

    void updateMoney();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* smallFont;
    TTF_Font* bigFont;
    TTF_Font* standardFont;

    Uint32 announcementStartTime;  
    const Uint32 announcementDuration = 10000;

    bool isRunning;
};


#endif