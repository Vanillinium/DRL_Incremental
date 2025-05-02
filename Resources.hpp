// Resources.hpp
#include "game.hpp"

#pragma once

// Window
extern const int WIDTH;
extern const int HEIGHT;
extern SDL_Color color;

// Main game components
extern int money;
extern double displayed_DRL;
extern int increment[];
extern int incrementIndex;

extern int decaySubtractAmount;
extern bool naturalDecay;
extern int clickCounter;
extern double CPS;
extern double CPSThreshold;

extern bool inDanger;
extern int dangerThreshold;

// Main box
extern SDL_Texture* main_box;
extern SDL_Rect rect_main_box;
extern bool isMainBoxClicked;
extern bool forceClickingDisabled;

// Upgrade box
extern SDL_Texture* upgrade_box;
extern SDL_Rect rect_upgrade_box;
extern int upgradeThreshold[];
extern int upgradeThresholdIndex;
extern int cost[];
extern int costIndex;
extern bool upgrade[];
extern int upgradeIndex;
extern bool isUpgradeBoxClicked;
extern bool isUpgradeAvaliableAnnouncementDisplayed;
extern bool isUpgradeBoxClickedDisplayed;

// Text
extern SDL_Color textColor;
extern SDL_Texture* mainTextTexture;
extern std::vector<SDL_Texture*> announcementTextTexture;
extern SDL_Texture* randomTextTexture;
extern std::string mainText;
extern std::string announcementText;
extern std::string randomText;
extern SDL_Rect mainTextRect;
extern std::vector<SDL_Rect> announcementTextRect;
extern SDL_Rect randomTextRect;

// Other textures
extern SDL_Texture* bg;

// Fonts
extern TTF_Font* smallFont;
extern TTF_Font* bigFont;
extern TTF_Font* standardFont;

// Timers
extern const Uint32 announcementDuration;
extern Uint32 announcementStartTime;
extern Uint32 idleTime;
extern Uint32 maxIdleTime;
extern Uint32 disableStart;
extern Uint32 disableMax;
extern Uint32 subtractedStart;
extern Uint32 subtractedInterval;
extern Uint32 dangerStart;
extern Uint32 dangerMax;
extern Uint32 counterStart;
extern Uint32 counterInterval;
