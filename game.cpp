#include "game.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"

#include "Resources.cpp"

using namespace std;

// GAME INITIALIZING
Game::Game(){}
Game::~Game(){}

// MAIN MECHANICS
void Game::reloadMainText(){
    if (mainTextTexture) SDL_DestroyTexture(mainTextTexture);
    mainTextTexture = FontManager::RenderText(mainText, standardFont, textColor, renderer, mainTextRect, 500);
}

void Game::reloadAnnouncementText(){
    for(auto& tex : announcementTextTexture){
        SDL_DestroyTexture(tex);
    }
    announcementTextTexture.clear();
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

void Game::decay(Uint32 now){

    if(now - subtractedStart >= subtractedInterval){
        money -= debuffedStateMoneySubtractAmount;
        displayed_DRL = (double) money / 10;

        updateMoneyText();

        subtractedStart = now;
    }
}

void Game::forceDisable(Uint32 now){
    if(!forceClickingDisabled){
        forceClickingDisabled = true;
        disableStart = SDL_GetTicks();

        announcementText = "Overloaded!\nClicking disabled.";
        reloadAnnouncementText();
    }
}

void Game::updateForceDisable(Uint32 now){
    if(forceClickingDisabled && now - disableStart >= disableMax){
        forceClickingDisabled = false;

        announcementText = "Clicking re-enabled!";
        reloadAnnouncementText();
    }
}

void Game::overload(Uint32 now){

    if(now - counterStart >= counterInterval){
        CPS = (double) clickCounter / (double) (now - counterStart) * 1000;

        if(CPS >= CPSThreshold && !forceClickingDisabled){
            forceDisable(now);
        }
        counterStart = now;
        cout << CPS << endl;
        clickCounter = 0;
    }
}

void Game::box1CheckCondition(){
    // annoucement: can upgrade.
    if(money >= 800 && !isBox1Clicked && !box1Annoucement_Displayed){
        // cond:
        // - drl is higher than 80 (money is 800).
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
        // +0.1/click -> +0.5/click
        // - 25 DRL
        increment = 4;
        money -= 250;
        displayed_DRL = (double) money / 10;

        // money subtracted = 1 DRL
        debuffedStateMoneySubtractAmount = 10;

        // update conds
        isBox1Clicked = true;
        box1Clicked_Displayed = true;

        //update money displaying
        updateMoneyText();
       
        // display announcementText
        announcementText = "Upgraded! You get 0.5 DRL for every class you attended!\n\nDRL Decay has been activated.\nYou will got your DRL subtracted if you\nhaven't attended any classes for a while";

        reloadAnnouncementText();
        announcementStartTime = SDL_GetTicks();
    }
}

void Game::box2CheckCondition(){
    // annoucement: can upgrade.
    if(money >= 1500 && !isBox2Clicked && !box2Annoucement_Displayed){
        // cond:
        // - drl is higher than 100 (money is 1000).
        // - the upgrade box has not been clicked before.
        // - the annoucement has not been displayed before.
        box2Annoucement_Displayed = true;

        //display announcementText
        announcementText =  "You can now purchase the second upgrade!\nThis upgrade will cost 50 DRL.\n";

        reloadAnnouncementText();
        announcementStartTime = SDL_GetTicks();
    }  
    
    // when clicked in the upgrade box.
    if(Upgrade2 && !box2Clicked_Displayed){
        // +0.5/click -> +1/click
        // - 50 DRL
        increment = 10;
        money -= 500;
        displayed_DRL = (double) money / 10;

        // CPS Cap -> 7.5CPS
        // decay interval = 1.5s
        CPSThreshold = 7.5;
        subtractedInterval = 1500;

        // update conds
        isBox2Clicked = true;
        box2Clicked_Displayed = true;

        //update money displaying
        updateMoneyText();
       
        // display announcementText
        announcementText = "Upgraded! You get 1 DRL for every class you attended!\n\nYou are now suffering from mental overload...\nYou won't be able to attend classes for\nawhile if you sessions are too rapid.";
        reloadAnnouncementText();
        announcementStartTime = SDL_GetTicks();
    }
}

void Game::box3CheckCondition(){
    // annoucement: can upgrade.
    if(money >= 2500 && !isBox3Clicked && !box3Annoucement_Displayed){
        // cond:
        // - drl is higher than 250 (money is 2500).
        // - the upgrade box has not been clicked before.
        // - the annoucement has not been displayed before.
        box3Annoucement_Displayed = true;

        //display announcementText
        announcementText =  "You can now purchase the third upgrade!\nThis upgrade will cost 225 DRL.\n";

        reloadAnnouncementText();
        announcementStartTime = SDL_GetTicks();
    }  
    
    // when clicked in the upgrade box.
    if(Upgrade3 && !box3Clicked_Displayed){
        // +1/click -> +2click
        // - 200 DRL
        increment = 20;
        money -= 2000;
        displayed_DRL = (double) money / 10;

        // money subtracted = 2 DRL
        // subtract interval = 1s
        debuffedStateMoneySubtractAmount = 20;
        subtractedInterval = 1000;

        // change danger threshold to 100 DRL instead of 70
        dangerThreshold = 1250;

        // update conds
        isBox3Clicked = true;
        box3Clicked_Displayed = true;

        //update money displaying
        updateMoneyText();
       
        // display announcementText
        announcementText = "Upgraded! You are now getting 2 DRL per class attended!\nDRL Decay has gotten even stronger...\nFailing grade has been increased.";

        reloadAnnouncementText();
        announcementStartTime = SDL_GetTicks();
    }
}

void Game::clickedInBoxCheckCondition(){
    if(isMainBoxClicked){
        money += increment;
        displayed_DRL = (double) money / 10;

        updateMoneyText();

        // reset idle counter when clicked
        idleTime = SDL_GetTicks();

        // increase clicking counter
        clickCounter++;
        
        // reset clicking cond
        isMainBoxClicked = false;

        
    }
}

void Game::gameOver(){
    Uint32 now = SDL_GetTicks();
    
    if(money < dangerThreshold){
        if(!inDanger){
            inDanger = true;
            dangerStart = now;

            if(randomTextTexture) SDL_DestroyTexture(randomTextTexture);
            randomTextTexture = FontManager::RenderText("In danger.", bigFont, textColor, renderer, randomTextRect, 250);
        }
        
        if(now - dangerStart >= dangerMax){
            isRunning = false;
        }
    }

    else{
        dangerStart = 0;
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
        upgrade_box2 = TextureManager::LoadTexture("assets/upgrade_box1.png", renderer);
        upgrade_box3 = TextureManager::LoadTexture("assets/upgrade_box1.png", renderer);
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
            if(SDL_PointInRect(&mousePosition, &rect_main_box) && !forceClickingDisabled){
                isMainBoxClicked = true;
            }

            // upgrades
            if(SDL_PointInRect(&mousePosition, &rect_upgrade_box1) && money >= 800 && !isBox1Clicked){
                Upgrade1 = true;
            }

            if(SDL_PointInRect(&mousePosition, &rect_upgrade_box2) && money >= 1500 && !isBox2Clicked){
                Upgrade2 = true;
            }
            if(SDL_PointInRect(&mousePosition, &rect_upgrade_box3) && money >= 2500 && !isBox3Clicked){
                Upgrade3 = true;
            }
            break;

        default:
            break;
    }
}

void Game::update(){ // game updates
    Uint32 now = SDL_GetTicks();
    // force quit game :3 
    gameOver();

    // for each click:
    clickedInBoxCheckCondition();

    //  FOR UPGRADE BOX
    box1CheckCondition();
    box2CheckCondition();
    box3CheckCondition();
    // check for idle: after 5 seconds, subtract [debuff amount] DRL/2.5s
    if(SDL_GetTicks() - idleTime >= maxIdleTime){
        decay(now);
    }

    // force disable
    overload(now);
    updateForceDisable(now);
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

    if(!isBox2Clicked && box2Annoucement_Displayed){
        SDL_RenderCopy(renderer, upgrade_box2, NULL , &rect_upgrade_box2);
    }
    if(!isBox3Clicked && box3Annoucement_Displayed){
        SDL_RenderCopy(renderer, upgrade_box3, NULL , &rect_upgrade_box3);
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
    if(upgrade_box2) SDL_DestroyTexture(upgrade_box2);
    if(upgrade_box3) SDL_DestroyTexture(upgrade_box3);

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


