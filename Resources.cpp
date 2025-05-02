#include "Resources.hpp"
#include "game.hpp"
using namespace std;

// window
const int WIDTH = 800, HEIGHT = 600;
SDL_Color color = {255, 255, 0, 0};

// main game compoments
int money = 700;                                                            // main currency
double displayed_DRL = 0;                                                   // displayed DRL: /10 money
int increment[] = {1, 2, 5, 8, 10, 15, 20, 30, 50, 80, 100, 9999999};                // formula: money = money + increment
int incrementIndex = 0;

int decaySubtractAmount = 1;
bool naturalDecay = true;
int clickCounter = 0;
double CPS = 0;
double CPSThreshold = 999;

bool inDanger;
int dangerThreshold = 700;

// for main box
    // texture
SDL_Texture* main_box;
SDL_Rect rect_main_box = {(WIDTH - 325) / 2,300,325,100};
    // logic
bool isMainBoxClicked = false;
bool forceClickingDisabled = false;

// for upgrade box
    // texture
SDL_Texture* upgrade_box;
SDL_Rect rect_upgrade_box = {(WIDTH - 325) / 2,100,325,100};
    // logic
int upgradeThreshold[] = {750, 850, 1000, 1250, 1500, 2000, 3000, 4500, 6000, 10000, 99999999};
int upgradeThresholdIndex = 0;

int cost[] = {75, 200, 400, 750, 1000, 1500, 2000, 4000, 5500, 9000, 9999999};
int costIndex = 0;

bool upgrade[] = {false, false, false, false, false, false, false, false, false, false, false};
int upgradeIndex = 0;

bool isUpgradeBoxClicked = false;
bool isUpgradeAvaliableAnnouncementDisplayed = false;
bool isUpgradeBoxClickedDisplayed = false;

// text
SDL_Color textColor = {255,255,255};

SDL_Texture* mainTextTexture;
vector <SDL_Texture*> announcementTextTexture;
SDL_Texture* randomTextTexture;

string mainText = "You currently have 70 DRL";
string announcementText = "";
string randomText = "";

SDL_Rect mainTextRect;
vector <SDL_Rect> announcementTextRect;
SDL_Rect randomTextRect;

// other textures
SDL_Texture* bg;

TTF_Font* smallFont;
TTF_Font* bigFont;
TTF_Font* standardFont;

// timers

const Uint32 announcementDuration = 10000;
Uint32 announcementStartTime = 0;

Uint32 idleTime = 0;
Uint32 maxIdleTime = 5000;

Uint32 disableStart = 0;
Uint32 disableMax = 5000;

Uint32 subtractedStart = 0;
Uint32 subtractedInterval = 2500;

Uint32 dangerStart = 0;
Uint32 dangerMax = 10000;

Uint32 counterStart = 0;
Uint32 counterInterval = 1000;