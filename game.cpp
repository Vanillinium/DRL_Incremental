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
        money -= decaySubtractAmount;
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
        cout << "[overloadChecker] CPS : " << CPS << endl;
        clickCounter = 0;
    }
}

void Game::upgradeBoxCheckCondition(){
    // annoucement: can upgrade.
    if(money >= upgradeThreshold[upgradeThresholdIndex] && !isUpgradeBoxClicked && !isUpgradeAvaliableAnnouncementDisplayed){
        isUpgradeAvaliableAnnouncementDisplayed = true;

        //display announcementText
        announcementText =  "You can now purchase the next upgrade\nwith your hard-earned DRL!";

        reloadAnnouncementText();
        announcementStartTime = SDL_GetTicks();
    }  
    

    // when clicked in the upgrade box.
    if(isUpgradeBoxClicked && !isUpgradeBoxClickedDisplayed){
        // current upgrade: active
        upgrade[upgradeIndex] = true;
        // subtract money from current cost
        money -= cost[costIndex];

        // continuing to the next upgrade conditions: increment, upgrade, cost, threshold
        incrementIndex++;
        upgradeIndex++;
        costIndex++;
        upgradeThresholdIndex++;   

        // DEBUGGER
        cout        << "[nextUpgradeState] : upgradeIndex: " << upgradeIndex << endl 
                    <<  "costIndex: " << costIndex << " | cost: " << cost[costIndex] << endl
                    <<  "incrementIndex: " << incrementIndex << " | increment: " << increment[incrementIndex] << endl
                    <<  "upgradeThresholdIndex: " << upgradeThresholdIndex << " | threshold: " << upgradeThreshold[upgradeThresholdIndex] << endl;
        
        // update money after subtracting
        displayed_DRL = (double) money / 10;

        // update conds
        isUpgradeBoxClickedDisplayed = true;

        //update money displaying
        updateMoneyText();
       
        // display announcementText
        announcementText = "Upgraded!";

        reloadAnnouncementText();
        announcementStartTime = SDL_GetTicks();
    }
}

void Game::upgradeBoxReset(){       // reset the upgrade box's state once the next update level gets reached
    if(money >= cost[costIndex] && isUpgradeBoxClickedDisplayed){
        isUpgradeBoxClicked = false;
        isUpgradeAvaliableAnnouncementDisplayed = false;
        isUpgradeBoxClickedDisplayed = false;

        // DEBUGGING
        cout << "[upgradeBoxReset] Upgrade state resetted\n";
    }
}

// void upgradeLogics(){
//     if(upgrade[1]){

//     }
// }

void Game::clickedInBoxCheckCondition(){
    if(isMainBoxClicked){
        money += increment[incrementIndex];
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
        upgrade_box = TextureManager::LoadTexture("assets/upgrade_box1.png", renderer);
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
                cout << "[handleEvents] Main box clicked!" << endl;
            break;
            }

            // upgrades
            if(SDL_PointInRect(&mousePosition, &rect_upgrade_box) && money >= cost[costIndex] && !isUpgradeBoxClicked){
                
                isUpgradeBoxClicked = true;
                cout << "[handleEvents] Upgrade box clicked!" << endl;
            break;
            }
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
    upgradeBoxReset();
    upgradeBoxCheckCondition();


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

    if(!isUpgradeBoxClicked && isUpgradeAvaliableAnnouncementDisplayed){
        SDL_RenderCopy(renderer, upgrade_box, NULL , &rect_upgrade_box);
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
    if(upgrade_box) SDL_DestroyTexture(upgrade_box);

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


