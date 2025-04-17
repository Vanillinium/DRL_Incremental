#include "Resources.hpp"
using namespace std;

// window
const int WIDTH = 800, HEIGHT = 600;
SDL_Color color = {255, 255, 0, 0};

// main game compoments
int money = 700;                                    // main currency
double displayed_DRL = 0;                           // displayed DRL: /10 money
int increment = 1;                                 // formula: money = money + increment

int debuffedStateMoneySubtractAmount = 1;

int clickCounter = 0;
double CPS = 0;
int CPSThreshold = 999;

bool inDanger;
int dangerThreshold = 700;

// for main box
    // texture
SDL_Texture* main_box;
SDL_Rect rect_main_box = {(WIDTH - 325) / 2,300,325,100};
    // logic
bool isMainBoxClicked = false;
bool forceClickingDisabled = false;

// for first upgrade box: 85+ DRL, cost 25 DRL
    // texture
SDL_Texture* upgrade_box1;
SDL_Rect rect_upgrade_box1 = {(WIDTH - 325) / 2,100,325,100};
    // logic
bool Upgrade1 = false;
bool isBox1Clicked = false;
bool box1Annoucement_Displayed = false;
bool box1Clicked_Displayed = false;


// for second upgrade box: 100+ DRL, cost 50 DRL
    // texture
SDL_Texture* upgrade_box2;
SDL_Rect rect_upgrade_box2 = {(WIDTH - 325) / 2,100,325,100};
    // logic
bool Upgrade2 = false;
bool isBox2Clicked = false;
bool box2Annoucement_Displayed = false;
bool box2Clicked_Displayed = false;

// for second upgrade box: 250+ DRL, cost 225 DRL
    // texture
SDL_Texture* upgrade_box3;
SDL_Rect rect_upgrade_box3 = {(WIDTH - 325) / 2,100,325,100};
    // logic
bool Upgrade3 = false;
bool isBox3Clicked = false;
bool box3Annoucement_Displayed = false;
bool box3Clicked_Displayed = false;


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