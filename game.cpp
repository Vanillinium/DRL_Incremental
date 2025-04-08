#include "game.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"

#include "Resources.cpp"
using namespace std;

// GAME INITIALIZING
Game::Game(){}
Game::~Game(){}

void Game::reloadMainText(){
    if (mainTextTexture) SDL_DestroyTexture(mainTextTexture);
    mainTextTexture = FontManager::RenderText(mainText, standardFont, textColor, renderer, mainTextRect, 500);
}

void Game::reloadAnnouncementText(){
    for(auto& tex : announcementTextTexture){
        SDL_DestroyTexture(tex);
    }

    announcementTextTexture = FontManager::RenderMultilineText(announcementText, smallFont, textColor, renderer, announcementTextRect, 50);
}

void Game::updateMoneyText(){
    stringstream ss;
        
    if (displayed_DRL == (int)displayed_DRL){
        mainText = "You currently have " + to_string((int)displayed_DRL) + " DRL";
    }

    else{
        ostringstream stream;
        stream << fixed << setprecision(1) << displayed_DRL;
        mainText = "You currently have " + stream.str() + " DRL";
    }
    reloadMainText();
}

void Game::moneyDecrease(){
    
    subtractedStart = SDL_GetTicks();

    if(subtractedStart - subtractedLast >= subtractedInterval){
        money -= debuffedStateMoneySubtractAmount;
        displayed_DRL = (double) money / 10;

        updateMoneyText();

        subtractedLast = subtractedStart;
    }
}

void Game::gameOver(){
    if(money < 699){
        inDanger = true;

        if(dangerLast == 0){
            randomTextTexture = FontManager::RenderText("In danger.", bigFont, textColor, renderer, randomTextRect, 300);
            dangerStart = SDL_GetTicks();
            dangerLast = dangerStart;
        }
        
        if(SDL_GetTicks() - dangerLast >= dangerMax) isRunning = false;
    }

    else{
        dangerLast = 0;
        inDanger = false;
    }
}

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
        bigFont = FontManager::LoadFont("assets/GenJyuuGothic-Bold.ttf", 48);

        mainTextTexture = FontManager::RenderText(mainText, standardFont, textColor, renderer, mainTextRect, 500);
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
            }
            break;

        default:
            break;
    }
}

void Game::update(){ // game updates

    // force quit game :3 
    gameOver();

    // for each click:
    if(isMainBoxClicked){
        money = money + upgrade + 1;
        displayed_DRL = (double) money / 10;

        updateMoneyText();

        // reset idle counter when clicked
        idleTime = SDL_GetTicks();

        // reset clicking cond
        isMainBoxClicked = false;
    }

    //
    //  FOR UPGRADE BOX#1
    // 

    // annoucement: can upgrade.
    if(money >= 750 && !isBox1Clicked && !box1Annoucement_Displayed){
        // cond:
        // - drl is higher than 75 (money is 750).
        // - the upgrade box has not been clicked before.
        // - the annoucement has not been displayed before.
        box1Annoucement_Displayed = true;

        //display announcementText
        announcementText =  "You can now purchase the first upgrade!\nThis upgrade will cost 15 DRL.\n";

        reloadAnnouncementText();
        announcementStartTime = SDL_GetTicks();
    }  
    
    // when clicked in the upgrade box.
    if(Upgrade1 && !box1Clicked_Displayed){
        // +1/click -> +3/click
        // - 5 DRL
        upgrade = 2;
        money -= 150;
        displayed_DRL = (double) money / 10;
        debuffedStateMoneySubtractAmount = 5;

        // update conds
        isBox1Clicked = true;
        box1Clicked_Displayed = true;

        //update money displaying
        updateMoneyText();
       
        // display announcementText
        announcementText = "Upgraded! You get 0.2 more DRL per click!\nDRL Decay has been increased.";

        reloadAnnouncementText();
        announcementStartTime = SDL_GetTicks();
    }

    // check for idle: after 5 seconds, subtract [debuff amount] DRL/2.5s
    if(SDL_GetTicks() - idleTime >= maxIdleTime){
        moneyDecrease();
    }
}

void Game::render(){ // renderer
    SDL_RenderClear(renderer); //refresh renderer

// all textures below

    // BACKGROUND
    SDL_RenderCopy(renderer, bg, NULL , NULL);

    // OBJECTS
    SDL_RenderCopy(renderer, main_box, NULL , &rect_main_box);
    if(!isBox1Clicked && box1Annoucement_Displayed){
        SDL_RenderCopy(renderer, upgrade_box1, NULL , &rect_upgrade_box1);
    }

    // that la 1 ngay tuyet voi lam mai deo biet hien chu tren man hinh kieu cac j
    // TEXT

        // ONLY LOAD WHEN UPDATING
    if(mainTextTexture) SDL_RenderCopy(renderer, mainTextTexture, NULL, &mainTextRect);
    if(inDanger) SDL_RenderCopy(renderer, randomTextTexture, NULL, &randomTextRect);

        // LOAD announcementText ONLY FOR 10 SECONDS
    if(SDL_GetTicks() - announcementStartTime < announcementDuration){
        for (size_t i = 0; i < announcementTextTexture.size(); i++) {
            SDL_RenderCopy(renderer, announcementTextTexture[i], NULL, &announcementTextRect[i]);
        }
    }
    
    // REFRESH
    SDL_RenderPresent(renderer);
}

void Game::clean(){

    // cleaning textures
        // font
    if(mainTextTexture) SDL_DestroyTexture(mainTextTexture);
    if(randomTextTexture) SDL_DestroyTexture(randomTextTexture);
    for(auto& tex : announcementTextTexture) {
        SDL_DestroyTexture(tex);
    }
        // textures
    if(main_box) SDL_DestroyTexture(main_box);
    if(bg) SDL_DestroyTexture(bg);
    if(upgrade_box1) SDL_DestroyTexture(upgrade_box1);
    

    // cleaning fonts
    if(standardFont) TTF_CloseFont(standardFont);
    if(smallFont) TTF_CloseFont(smallFont);
    if(bigFont) TTF_CloseFont(bigFont);

    TTF_Quit();

    // cleaning window
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);

    SDL_Quit();
}

bool Game::running(){ // self explantory
    return isRunning;
}

