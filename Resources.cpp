#include "Resources.hpp"
#include "game.hpp"
using namespace std;

//---------------------------WINDOW-------------------------------//
const int WIDTH = 800, HEIGHT = 600;
SDL_Color color = {255, 255, 0, 0};


//-------------------------GAME STATE-----------------------------//
GameState currentGameState = MENU;
Uint32 resultEnterTime = 0;
const Uint32 resultDelay = 5000;

//---------------------------MENU--------------------------------//
SDL_Texture* playButtonTexture = NULL;
SDL_Rect playButtonRect = {WIDTH / 2 - 150, HEIGHT / 2 + 50, 300, 100};

SDL_Texture* quitButtonTexture = NULL;
SDL_Rect quitButtonRect = {WIDTH / 2 - 150, HEIGHT / 2 + 150, 300, 100};

SDL_Texture* gameTitleTexture = NULL;
SDL_Rect gameTitleRect = {WIDTH / 2 - 250, 50, 500, 200};

SDL_Texture* menuBackgroundTexture = NULL;

//--------------------------TUTORIAL------------------------------//
SDL_Texture* tutorialBackgroundTexture = NULL;
SDL_Rect tutorialBackgroundRect = {0, 0, WIDTH, HEIGHT};

//-------------------------GAME OVER------------------------------//
SDL_Texture* gameOverBackgroundTexture = NULL;
SDL_Rect gameOverBackgroundRect = {0, 0, WIDTH, HEIGHT};

//----------------------------WIN---------------------------------//
SDL_Texture* winBackgroundTexture = NULL;
SDL_Rect winBackgroundRect = {0, 0, WIDTH, HEIGHT};


//---------------------------MONEY ------------------------------//
int money = 700;                                                            // main currency
double displayed_DRL = 0;                                                   // displayed DRL: /10 money
int increment[] = {1, 2, 5, 8, 10, 15, 20, 30, 50, 80, 100, 9999999};       // formula: money = money + increment
int incrementIndex = 0;

//--------------------------MECHANICS---------------------------//
// MECHANIC: DECAY
    // IDLE CHECK
Uint32 idleTime = 0;                                                       
Uint32 maxIdleTime = 5000;
    // DECAY
int decaySubtractAmount = 0;
bool naturalDecay = true;

Uint32 subtractedStart = 0;
Uint32 subtractedInterval = 1500;

// MECHANIC: OVERLOAD
    // CALCULATING CPS
int clickCounter = 0;
double CPS = 0;
double CPSThreshold = 999;

Uint32 clickCounterStart = 0;
Uint32 const clickCounterInterval = 1000;

    // FORCE DISABLE   
Uint32 disableStart = 0;
Uint32 disableMax = 5000;

// MECHANIC: DANGER STATE
bool inDanger;
int dangerThreshold = 700;

Uint32 dangerStart = 0;
Uint32 dangerMax = 10000;

// MECHANIC: LEECH
int leechCount  = 0;
int leechMax = 0;
int leechSubtractAmount = 15;

Uint32 leechSpawnStart = 0;
Uint32 leechSpawnInterval = 10000;

Uint32 leechSubtractStart = 0;
Uint32 leechSubtractInterval = 2500;

    // TEXTURE
SDL_Texture* leechTexture = nullptr;
std::vector<SDL_Rect> leechRects;


// MECHANIC: BONUS MONEY
double MPS = 0;
int moneyCounter = 0;
double bonusMoneyMultiplier = 0;

Uint32 bonusMoneyStart = 0;
Uint32 bonusMoneyInterval = 10000;

//-----------------------MAIN BOX-------------------------//
    // TEXTURE
SDL_Texture* main_box;
SDL_Rect rect_main_box = {(WIDTH - 325) / 2,300,325,100};
    // LOGIC
bool isMainBoxClicked = false;
bool forceClickingDisabled = false;

//--------------------UPGRADE BOX-------------------------//
    // TEXTURE
SDL_Texture* upgrade_box;
SDL_Rect rect_upgrade_box = {(WIDTH - 325) / 2,100,325,100};

    // COND
int upgradeThreshold[] = {750, 850, 1000, 1250, 1500, 2000, 3000, 4500, 6000, 10000, 99999999};
int upgradeThresholdIndex = 0;

    // COST
int cost[] = {75, 200, 400, 750, 1000, 1500, 2000, 4000, 5500, 9000, 9999999};
int costIndex = 0;

    // UPGRADE COUNTER
bool upgrade[] = {false, false, false, false, false, false, false, false, false, false, false};
int upgradeIndex = 0;

    // LOGICS
bool isUpgradeBoxClicked = false;
bool isUpgradeAvaliableAnnouncementDisplayed = false;
bool isUpgradeBoxClickedDisplayed = false;

//-----------------------TEXT----------------------------//
    // FONTS
TTF_Font* smallFont;
TTF_Font* bigFont;
TTF_Font* standardFont;

    // COLOR
SDL_Color textColor = {255,255,255};

    // TEXTURE
SDL_Texture* mainTextTexture;
vector <SDL_Texture*> announcementTextTexture;
SDL_Texture* randomTextTexture;

    // TEXT STRINGS
string mainText = "You currently have 70 DRL";
string announcementText = "";
string randomText = "";

    // TARGET RECTS
SDL_Rect mainTextRect;
vector <SDL_Rect> announcementTextRect;
SDL_Rect randomTextRect;

    // LOGICS
const Uint32 announcementDuration = 10000;
Uint32 announcementStartTime = 0;

//------------------OTHER TEXTURES-------------------//
SDL_Texture* bg;

//---------------------MUSIC-------------------------//
    // STATE
GameState currentMusicState = MENU;
    // MUSIC
Mix_Music* bgMusic = nullptr;
Mix_Music* menuMusic = nullptr;
Mix_Music* gameOverMusic = nullptr;
Mix_Music* winMusic = nullptr;

    // SFX
Mix_Chunk* clickSound = nullptr;
Mix_Chunk* upgradeSound = nullptr;
Mix_Chunk* leechAppearSound = nullptr;