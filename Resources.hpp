#include "game.hpp"
#pragma once

//---------------------------WINDOW-------------------------------//
extern const int WIDTH;
extern const int HEIGHT;
extern SDL_Color color;

//-------------------------GAME STATE-----------------------------//
enum GameState {MENU, PLAYING, GAME_OVER, WIN};
extern GameState currentGameState;
extern Uint32 resultEnterTime;
extern const Uint32 resultDelay;

//---------------------------MENU--------------------------------//
extern SDL_Texture* playButtonTexture;
extern SDL_Rect playButtonRect;

extern SDL_Texture* quitButtonTexture;
extern SDL_Rect quitButtonRect;

extern SDL_Texture* gameTitleTexture;
extern SDL_Rect gameTitleRect;

extern SDL_Texture* menuBackgroundTexture;

//-------------------------GAME OVER------------------------------//
extern SDL_Texture* gameOverBackgroundTexture;
extern SDL_Rect gameOverBackgroundRect;

//----------------------------WIN---------------------------------//
extern SDL_Texture* winBackgroundTexture;
extern SDL_Rect winBackgroundRect;

//---------------------------MONEY ------------------------------//
extern int money;
extern double displayed_DRL;
extern int increment[];
extern int incrementIndex;

//--------------------------MECHANICS---------------------------//
// MECHANIC: DECAY
    // IDLE CHECK
extern Uint32 idleTime;
extern Uint32 maxIdleTime;
    // DECAY
extern int decaySubtractAmount;
extern bool naturalDecay;

extern Uint32 subtractedStart;
extern Uint32 subtractedInterval;

// MECHANIC: OVERLOAD
    // CALCULATING CPS
extern int clickCounter;
extern double CPS;
extern double CPSThreshold;

extern Uint32 clickCounterStart;
extern const Uint32 clickCounterInterval;

    // FORCE DISABLE
extern Uint32 disableStart;
extern Uint32 disableMax;

// MECHANIC: DANGER STATE
extern bool inDanger;
extern int dangerThreshold;

extern Uint32 dangerStart;
extern Uint32 dangerMax;

// MECHANIC: LEECH
extern int leechCount;
extern int leechMax;
extern int leechSubtractAmount;

extern Uint32 leechSpawnStart;
extern Uint32 leechSpawnInterval;

extern Uint32 leechSubtractStart;
extern Uint32 leechSubtractInterval;

    // TEXTURE
extern SDL_Texture* leechTexture;
extern std::vector<SDL_Rect> leechRects;

// MECHANIC: BONUS MONEY
extern double MPS;
extern int moneyCounter;
extern double bonusMoneyMultiplier;

extern Uint32 bonusMoneyStart;
extern Uint32 bonusMoneyInterval;


//-----------------------MAIN BOX-------------------------//
extern SDL_Texture* main_box;
extern SDL_Rect rect_main_box;
extern bool isMainBoxClicked;
extern bool forceClickingDisabled;

//--------------------UPGRADE BOX-------------------------//
    // TEXTURE
extern SDL_Texture* upgrade_box;
extern SDL_Rect rect_upgrade_box;

    // CONDITION
extern int upgradeThreshold[];
extern int upgradeThresholdIndex;

    // COST
extern int cost[];
extern int costIndex;

    // COUNTER
extern bool upgrade[];
extern int upgradeIndex;

    // LOGICS
extern bool isUpgradeBoxClicked;
extern bool isUpgradeAvaliableAnnouncementDisplayed;
extern bool isUpgradeBoxClickedDisplayed;

//-------------------------TEXT---------------------------//
    // FONTS
extern TTF_Font* smallFont;
extern TTF_Font* bigFont;
extern TTF_Font* standardFont;

    // COLOR
extern SDL_Color textColor;

    // TEXTURE
extern SDL_Texture* mainTextTexture;
extern std::vector<SDL_Texture*> announcementTextTexture;
extern SDL_Texture* randomTextTexture;

    // TEXT STRING
extern std::string mainText;
extern std::string announcementText;
extern std::string randomText;

    // TARGET RECT
extern SDL_Rect mainTextRect;
extern std::vector<SDL_Rect> announcementTextRect;
extern SDL_Rect randomTextRect;

    // LOGICS
extern const Uint32 announcementDuration;
extern Uint32 announcementStartTime;

//---------------OTHER TEXTURES-------------------//
extern SDL_Texture* bg;

//---------------------MUSIC-------------------------//
    // GAME STATE
extern GameState currentMusicState;
    // BGM
extern Mix_Music* bgMusic;
extern Mix_Music* menuMusic;
extern Mix_Music* gameOverMusic;
extern Mix_Music* winMusic;

    // SFX
extern Mix_Chunk* clickSound;
extern Mix_Chunk* upgradeSound;
extern Mix_Chunk* leechAppearSound;

















