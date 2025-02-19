#include "game.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
using namespace std;

// variables
const int WIDTH = 800, HEIGHT = 600;
SDL_Texture* image;
SDL_Texture* main_box;
SDL_Rect rect_box = {(WIDTH/2)-162,300,325,100};

// GAME INITIALIZING
Game::Game(){}
Game::~Game(){}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){ // initializer
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){ // initialized successfully
        cout << "Program initialized successfully...\n"; 
        
        // WINDOWS 
        int flags = 0; 
        if(fullscreen == true){flags = SDL_WINDOW_FULLSCREEN;} // fullscreen flag

        window = SDL_CreateWindow("test", xpos, ypos, width, height, flags); 
        if(window){cout << "Window created successfully...\n";} // window successfully created

        // RENDERER
        renderer = SDL_CreateRenderer(window, -1,0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer created successfully...\n"; // renderer successfully created
        } 

        // STATUS
        isRunning = true;
    }

    else{isRunning = false; cout << "Program initialization failed.\n";} // initialize failed
}

void Game::handleEvents(){ // events
    SDL_Event event;
    SDL_PollEvent(&event); // queueing events

    mousePosition.x = event.motion.x; 
    mousePosition.y = event.motion.y; // for mouse detection

    // main events below
    switch(event.type){
        case SDL_QUIT:  // close button pressed
            isRunning = false; 
            break;
        case SDL_MOUSEBUTTONDOWN: // mouse button is down
            if(SDL_PointInRect(&mousePosition, &rect_box)){
                ClickedInBox = true;
            }
            break;
        default:
            break;
    }

}

void Game::update(){ // game updates
    // click detection
    if(ClickedInBox){
        money += 1;
        cout << "Clicked! You currently have " << money <<"!\n";
        ClickedInBox = false;
    }
}

void Game::render(){ // renderer
    SDL_RenderClear(renderer); //refresh renderer
// all textures below
    main_box = TextureManager::LoadTexture("assets/box.png", renderer);
    SDL_RenderCopy(renderer, main_box, NULL , &rect_box);
    SDL_RenderPresent(renderer);

}

void Game::clean(){ // self explantory
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_QUIT;
    cout << "rip bozo\n";
}

bool Game::running(){ // self explantory
    return isRunning;
}

// MAIN FUNCT
int MAX_FPS = 60;
Game *game = nullptr;
int main(int argc, char *argv[]){
    game = new Game();

    game->init("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
    
    while(game->running()){
        SDL_Delay(1000/MAX_FPS);
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}   