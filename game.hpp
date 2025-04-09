#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
using namespace std;

class Game{

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

    // OTHER FUNCTIONS
    void decay(Uint32 now);
    void forceDisable(Uint32 now);
    void updateForceDisable(Uint32 now);
    void overload(Uint32 now);

    void clickedInBoxCheckCondition();
    void box1CheckCondition();
    void box2CheckCondition();

    void updateMoneyText();
    void reloadMainText();
    void reloadAnnouncementText();

    void gameOver();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* smallFont;
    TTF_Font* bigFont;
    TTF_Font* standardFont;

    // for click detection
    SDL_Point mousePosition;

    // timer thingy

    Uint32 now;

    Uint32 announcementStartTime;  
    const Uint32 announcementDuration = 10000;

    Uint32 idleTime;
    Uint32 maxIdleTime = 5000;

    Uint32 disableStart;
    Uint32 disableMax = 5000;

    Uint32 subtractedStart;
    Uint32 subtractedInterval = 2500;

    Uint32 dangerStart;
    Uint32 dangerMax = 10000;

    Uint32 counterStart;
    Uint32 counterInterval = 1000;

    bool isRunning;
};


#endif