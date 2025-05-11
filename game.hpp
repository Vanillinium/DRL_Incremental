#ifndef game_hpp
#define game_hpp

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

class Game{

public:
    Game();
    ~Game();

    // GAME INIT
    void init(const char* title, int xpos, int ypos, int wdth, int height, bool fullscreen);
    
    // MAIN COMPOMENTS
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();

    // MAIN MECHANICS
    void decay(Uint32 now);

    void forceDisable(Uint32 now);
    void updateForceDisable(Uint32 now);

    void overload(Uint32 now);

    void leechSpawn();
    void leechUpdate(Uint32 now);

    void bonusMoney(Uint32 now);

    // TEXT HANDLING
    void updateMoneyText();
    void reloadMainText();
    void reloadAnnouncementText();

    // CLICKING CHECK
    void clickedInBoxCheckCondition();

    // UPGRADE BOX CHECK
    void upgradeBoxCheckCondition();
    void upgradeBoxReset();
    void upgradeLogics();
    
    // RESULT
    void gameOver(Uint32 now);
    void gameWin(Uint32 now);
private:
    SDL_Window* window;
    SDL_Renderer* renderer; 
    SDL_Point mousePosition;
    bool isRunning;
};

#endif