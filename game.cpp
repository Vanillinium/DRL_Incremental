#include "game.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"

#include "Resources.cpp"
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

        // FONTS
        if(TTF_Init() == 0){
            cout << "Font library initialized successfully\n";
        }

        // PRELOAD TEXTURE
        standardFont = FontManager::LoadFont("assets/GenJyuuGothic-Bold.ttf", 30);
        smallFont = FontManager::LoadFont("assets/Nunito-ExtraLight.ttf", 24);
        bigFont = standardFont = FontManager::LoadFont("assets/GenJyuuGothic-Bold.ttf", 48);

        mainTextTexture = FontManager::RenderMainText(displayedText, standardFont, textColor, renderer, textRect);
        
        upgrade_box1 = TextureManager::LoadTexture("assets/upgrade_box1.png", renderer);
        main_box = TextureManager::LoadTexture("assets/box.png", renderer);
        bg = TextureManager::LoadTexture("assets/bg.jpg", renderer);

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

        case SDL_MOUSEBUTTONDOWN: // event: for when <mouse button> is down.
            // regular clicks
            if(SDL_PointInRect(&mousePosition, &rect_main_box)){
                isMainBoxClicked = true;
            }

            // upgrade 1
            if(SDL_PointInRect(&mousePosition, &rect_upgrade_box1) && money >= 750 && !isBox1Clicked){
                Upgrade1 = true;
                money -= 50;
            }
            break;

        default:
            break;
    }
}

void Game::updateMoney(){
    stringstream ss;
        
    if (displayed_DRL == (int)displayed_DRL){
        displayedText = "You currently have " + to_string((int)displayed_DRL) + " DRL";
    }

    else{
        ostringstream stream;
        stream << fixed << setprecision(1) << displayed_DRL;
        displayedText = "You currently have " + stream.str() + " DRL";
    }
}

void Game::update(){ // game updates
    
    // for each click:
    if(isMainBoxClicked){
        money = money + upgrade + 1;
        displayed_DRL = (double) money / 10;

        
        updateMoney();
        mainTextTexture = FontManager::RenderMainText(displayedText, standardFont, textColor, renderer, textRect);

        textRect.x = (WIDTH - textRect.w) / 2;  
        textRect.y = 500;  
        // cout << "Clicked! You currently have " << fixed << setprecision(1) << displayed_DRL <<" DRL!\n";
        isMainBoxClicked = false;
    }

    // for upgrade box 1:

    // annoucement: can upgrade.
    if(money >= 750 && !isBox1Clicked && !box1Annoucement_Displayed){
        // cond:
        // - drl is higher than 75 (money is 750).
        // - the upgrade box has not been clicked before.
        // - the annoucement has not been displayed before.
        box1Annoucement_Displayed = true;

        //display announcement
        announcement =  "You can now purchase the first upgrade!\nThis upgrade will cost 5 DRL.\n";

        announcementTextTexture = FontManager::RenderMultilineText(announcement, smallFont, textColor, renderer, announcementRect);
        announcementStartTime = SDL_GetTicks();
    }  
    
    // when clicked in the upgrade box.
    if(Upgrade1 && !box1Clicked_Displayed){
        updateMoney();
        // +1/click -> +3/click
        upgrade = 2;
        isBox1Clicked = true;
        box1Clicked_Displayed = true;

        // display announcement
        announcement = "Upgraded! You get 0.2 more DRL per click!\nDRL left: " + displayedText;
        announcementTextTexture = FontManager::RenderMultilineText(announcement, smallFont, textColor, renderer, announcementRect);

        announcementStartTime = SDL_GetTicks();
    }
}

void Game::render(){ // renderer
    SDL_RenderClear(renderer); //refresh renderer

// all textures below

    // BACKGROUND
    SDL_RenderCopy(renderer, bg, NULL , NULL);

    // OBJECTS
    SDL_RenderCopy(renderer, main_box, NULL , &rect_main_box);
    if(!isBox1Clicked && box1Annoucement_Displayed)
    SDL_RenderCopy(renderer, upgrade_box1, NULL , &rect_upgrade_box1);

    // that la 1 ngay tuyet voi lam mai deo biet hien chu tren man hinh kieu cac j
    // TEXT
        // ONLY LOAD WHEN UPDATING DRL
    if(mainTextTexture) SDL_RenderCopy(renderer, mainTextTexture, NULL, &textRect);

        // LOAD ANNOUNCEMENT ONLY FOR 10 SECONDS
    if(SDL_GetTicks() - announcementStartTime < announcementDuration){
        for (size_t i = 0; i < announcementTextTexture.size(); i++) {
            SDL_RenderCopy(renderer, announcementTextTexture[i], NULL, &announcementRect[i]);
        }
    }
    
    // REFRESH
    SDL_RenderPresent(renderer);
}

void Game::clean(){ // self explantory
    
    TTF_CloseFont(standardFont);
    TTF_CloseFont(smallFont);
    TTF_CloseFont(bigFont);
    TTF_Quit();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "rip bozo\n";
}

bool Game::running(){ // self explantory
    return isRunning;
}

