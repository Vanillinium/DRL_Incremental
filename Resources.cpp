#include "game.hpp"
using namespace std;

// window
const int WIDTH = 800, HEIGHT = 600;
SDL_Color color = {255, 255, 0, 0};

// main game compoments
int money = 700;                                    // main currency
double displayed_DRL = 0;                           // displayed DRL: /10 money
int upgrade = 0;                                    // upgrade counter: 
                                                    // formula: money = money + upgrade + 1
int debuffedStateMoneySubtractAmount = 1;

bool inDanger;
// for main box
    // texture
SDL_Texture* main_box;
SDL_Rect rect_main_box = {(WIDTH - 325) / 2,300,325,100};
    // logic
bool isMainBoxClicked = false;


// for first upgrade box: 5 DRL
    // texture
SDL_Texture* upgrade_box1;
SDL_Rect rect_upgrade_box1 = {(WIDTH - 325) / 2,100,325,100};
    // logic
bool Upgrade1 = false;
bool isBox1Clicked = false;
bool box1Annoucement_Displayed = false;
bool box1Clicked_Displayed = false;

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


