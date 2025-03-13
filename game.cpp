#include "game.hpp"
#include "TextureManager.hpp"
#include "Resources.hpp"
using namespace std;

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
            if(SDL_PointInRect(&mousePosition, &rect_main_box)){
                ClickedInBox = true;
            }
            // upgrade 1
            if(SDL_PointInRect(&mousePosition, &rect_special_box) && money >= 30 && !isClicked){
                Upgrade1 = true;
                money -= 30;
            }
            break;
        default:
            break;
    }

}
void Game::update(){ // game updates
    // click detection
    if(ClickedInBox){
        money = money + upgrade + 1;
        cout << "Clicked! You currently have " << money <<"!\n";
        ClickedInBox = false;
    }

    if(money >= 30 && !isClicked && !displayed){
        cout << "You can now purchase the first upgrade!\n";
        displayed = true;
    }  

    if(Upgrade1 && !displayed2){
        cout << "Upgraded! You get 2 more points per click!\n";
        // NOTE: lam ham invalid nut bam
        upgrade = 2;
        isClicked = true;
        displayed2 = true;
    }
}

void Game::render(){ // renderer
    SDL_RenderClear(renderer); //refresh renderer
// all textures below

    // const char* font = "assets/Nunito-ExtraLight.ttf";
    // TTF_Font* loadFont = TTF_OpenFont(font, 24);
    //     if(loadFont == NULL){
    //         SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    //     }
    
    // SDL_Color textColor = {255,255,255,255};
    // const char* text = "Test";
    // SDL_Texture* helloText = FontManager::LoadFont(font, 24, text, textColor, renderer);
    // int textWidth, textHeight;
    // SDL_QueryTexture(helloText, NULL, NULL, &textWidth, &textHeight);
    // SDL_Rect textRect = {100, 100, textWidth, textHeight};
    

    special_box = TextureManager::LoadTexture("assets/special_box.png", renderer);
    main_box = TextureManager::LoadTexture("assets/box.png", renderer);
    bg = TextureManager::LoadTexture("assets/bg.jpg", renderer);

    // SDL_RenderCopy(renderer, helloText, NULL, &textRect);
    SDL_RenderCopy(renderer, bg, NULL , NULL);
    SDL_RenderCopy(renderer, main_box, NULL , &rect_main_box);
    SDL_RenderCopy(renderer, special_box, NULL , &rect_special_box);
    SDL_RenderPresent(renderer);

    // TTF_CloseFont(loadFont);
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