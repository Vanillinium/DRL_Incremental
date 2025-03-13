#include "game.hpp"
using namespace std;

const int WIDTH = 800, HEIGHT = 600;

bool ClickedInBox = false;

bool Upgrade1 = false;
int money = 0; // currency
int upgrade = 0; // upgrade coubter

SDL_Point mousePosition;
SDL_Color color = {255, 255, 0, 0};

static SDL_Texture* special_box;

bool isClicked = false;
bool displayed = false;
bool displayed2 = false;

SDL_Texture* image;
SDL_Texture* main_box;
SDL_Texture* bg;


SDL_Rect rect_main_box = {(WIDTH/2)-162,300,325,100};
SDL_Rect rect_special_box = {(WIDTH/2)-162,100,325,100};