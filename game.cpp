#include "game.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "AudioManager.hpp"
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

        window = SDL_CreateWindow("DRL Incremental", xpos, ypos, width, height, flags); 
        if(window){cout << "[INIT] Window created successfully...\n";} // window successfully created

        // RENDERER
        renderer = SDL_CreateRenderer(window, -1,0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "[INIT] Renderer created successfully...\n"; // renderer successfully created
        }

        // FONTS
        if(TTF_Init() == 0){
            cout << "[INIT] Font library initialized successfully\n";
        }

        if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != 0){
            cout << "[INIT] Mixer library initialized successfully\n";
        }

        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0){
            cout << "[INIT] Mixer open audio successfully\n";
        }

        // PRELOADING TEXTURES
            // FONT
        standardFont = FontManager::LoadFont("assets/font/GenJyuuGothic-Bold.ttf", 30);
        smallFont = FontManager::LoadFont("assets/font/Nunito-ExtraLight.ttf", 24);
        bigFont = FontManager::LoadFont("assets/font/GenJyuuGothic-Bold.ttf", 48);

            // TEXT
        mainTextTexture = FontManager::RenderText(mainText, standardFont, textColor, renderer, mainTextRect, 500);

            // TEXTURE
        playButtonTexture = TextureManager::LoadTexture("assets/img/start_button.png", renderer);
        quitButtonTexture = TextureManager::LoadTexture("assets/img/quit_button.png", renderer);
        gameTitleTexture = TextureManager::LoadTexture("assets/img/title.png", renderer);
        
        upgrade_box = TextureManager::LoadTexture("assets/img/upgrade_box1.png", renderer); 
        main_box = TextureManager::LoadTexture("assets/img/box.png", renderer);
        leechTexture = TextureManager::LoadTexture("assets/img/leech.png", renderer);

            // BG
        menuBackgroundTexture = TextureManager::LoadTexture("assets/img/menu_bg.png", renderer);
        tutorialBackgroundTexture = TextureManager::LoadTexture("assets/img/tuto_main_1.png", renderer);
        bg = TextureManager::LoadTexture("assets/img/bg.jpg", renderer);
        gameOverBackgroundTexture = TextureManager::LoadTexture("assets/img/game_over.png", renderer);
        winBackgroundTexture = TextureManager::LoadTexture("assets/img/win.png", renderer);

            // MUSIC
        bgMusic = Mix_LoadMUS("assets/audio/bg1.mp3");
        menuMusic = Mix_LoadMUS("assets/audio/bgmenu.mp3");
        winMusic = Mix_LoadMUS("assets/audio/bgwin.mp3");
        gameOverMusic = Mix_LoadMUS("assets/audio/bggameover.mp3");

            // SFX
        clickSound = Mix_LoadWAV("assets/audio/click.wav");
        leechAppearSound = Mix_LoadWAV("assets/audio/leechappear.wav");
        upgradeSound = Mix_LoadWAV("assets/audio/upgrade.wav");

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
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_F12) {
                static bool consoleVisible = false;
                consoleVisible = !consoleVisible;

                if (consoleVisible) {
                    AllocConsole();
                    freopen("CONOUT$", "w", stdout);
                    freopen("CONOUT$", "w", stderr);
                    cout << "[Console] Console shown via F12\n";
                } 

                else {
                    std::cout << "[Console] Console hidden via F12\n";

                    // Reset stdout/stderr về NULL trước khi đóng console
                    fclose(stdout);
                    fclose(stderr);

                    FreeConsole();
                }
            }
            break;

        case SDL_MOUSEBUTTONDOWN: // event: for when <mouse button> is down.
            // MENU
            if(currentGameState == MENU){
                if(SDL_PointInRect(&mousePosition, &playButtonRect)){
                    currentGameState = TUTORIAL;
                    
                    cout << "[handleEvents] Play button clicked!" << endl;
                }
                else if(SDL_PointInRect(&mousePosition, &quitButtonRect)){
                    isRunning = false;

                    cout << "[handleEvents] Quit button clicked!" << endl;
                }
            }

            else if(currentGameState == TUTORIAL){
                currentGameState = PLAYING;

                // reset game state
                    money = 700;
                    displayed_DRL = (double)money / 10;

                    incrementIndex = 0;

                    Uint32 maxIdleTime = 5000;
                    decaySubtractAmount = 0;
                    subtractedInterval = 1500;

                    clickCounter = 0;
                    CPS = 0;
                    CPSThreshold = 999;

                    disableMax = 5000;
                    dangerThreshold = 700;

                    dangerMax = 10000;

                    leechCount  = 0;
                    leechMax = 0;
                    leechSubtractAmount = 15;
                    leechSpawnInterval = 10000;
                    leechSubtractInterval = 2500;

                    MPS = 0;
                    moneyCounter = 0;
                    bonusMoneyMultiplier = 0;
                    bonusMoneyInterval = 10000;


                    updateMoneyText();

                    Mix_HaltMusic();
                    Mix_PlayMusic(bgMusic, -1);

            }

            // INGAME

            else if(currentGameState == PLAYING){
                // regular clicks
                if(SDL_PointInRect(&mousePosition, &rect_main_box) && !forceClickingDisabled){
                
                    isMainBoxClicked = true;
                    // cout << "[handleEvents] Main box clicked!" << endl;

                    break;
                }

                // upgrades
                if(SDL_PointInRect(&mousePosition, &rect_upgrade_box) && money >= cost[costIndex] && !isUpgradeBoxClicked){
                
                    isUpgradeBoxClicked = true;
                    cout << "[handleEvents] Upgrade box clicked!" << endl;

                    break;
                }

                for(size_t i = 0; i < leechRects.size(); ++i){
                    if(SDL_PointInRect(&mousePosition, &leechRects[i]) && !forceClickingDisabled){
                        leechRects.erase(leechRects.begin() + i);
                        leechCount--;

                        cout << "[handleEvents] Leech clicked!" << endl;
                        cout << "[leechChecker] Leech deleted!" << endl;
                        cout << "[leechChecker] Leech count: " << leechCount << endl;

                    break;
                    }
                }
            }

            else if(currentGameState == GAME_OVER || currentGameState == WIN){
                if (SDL_GetTicks() - resultEnterTime >= resultDelay){
                    currentGameState = MENU;
                }              
            }

        default: break;
    }
}

void Game::update(){ // game updates
    Uint32 now = SDL_GetTicks();

    // bgm
    AudioManager audio;
    audio.playBGMForState(currentGameState);

    // If game state != playing, do not update
    if(currentGameState == PLAYING){

        // change gamestate
        gameWin(now);
        gameOver(now);

        // FOR EACH CLICK:
        clickedInBoxCheckCondition();

        // FOR LEECH
        leechUpdate(now);

        //  FOR UPGRADE BOX
        upgradeBoxReset();
        upgradeBoxCheckCondition();

        upgradeLogics();

        // check for idle: after maxIdleTime, subtract [debuff amount] DRL per decayInterval
        if(SDL_GetTicks() - idleTime >= maxIdleTime && naturalDecay){
            decay(now);
        }

        // OVERLOAD
        overload(now);
        updateForceDisable(now);

        // BONUS
        bonusMoney(now);
    }
}

void Game::render(){ // renderer
    SDL_RenderClear(renderer); //refresh renderer

// all textures below

    if(currentGameState == MENU){
            // BG
        SDL_RenderCopy(renderer, menuBackgroundTexture, NULL , NULL);

            // TITLE
        SDL_RenderCopy(renderer, gameTitleTexture, NULL , &gameTitleRect);
    
            // BUTTONS
        SDL_RenderCopy(renderer, playButtonTexture, NULL , &playButtonRect);
        SDL_RenderCopy(renderer, quitButtonTexture, NULL , &quitButtonRect);    
    }

    else if(currentGameState == TUTORIAL){
            // BACKGROUND
        SDL_RenderCopy(renderer, tutorialBackgroundTexture, NULL, &tutorialBackgroundRect);
    }

    else if(currentGameState == PLAYING){
            // BACKGROUND
        SDL_RenderCopy(renderer, bg, NULL , NULL);

            // OBJECTS
        SDL_RenderCopy(renderer, main_box, NULL , &rect_main_box);

        if(!isUpgradeBoxClicked && isUpgradeAvaliableAnnouncementDisplayed){
            SDL_RenderCopy(renderer, upgrade_box, NULL , &rect_upgrade_box);
        }

        for(const auto&rect : leechRects) {
            SDL_RenderCopy(renderer, leechTexture, NULL, &rect);
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
    }

    else if(currentGameState == GAME_OVER){
        SDL_RenderCopy(renderer, gameOverBackgroundTexture, NULL , &gameOverBackgroundRect);
    }

    else if(currentGameState == WIN){
        SDL_RenderCopy(renderer, winBackgroundTexture, NULL , &winBackgroundRect);
    }

    // REFRESH
    SDL_RenderPresent(renderer);
}

void Game::clean(){


    // cleaning textures
        // text
    if(mainTextTexture) SDL_DestroyTexture(mainTextTexture);
    if(randomTextTexture) SDL_DestroyTexture(randomTextTexture);
    for(auto& tex : announcementTextTexture) {
        SDL_DestroyTexture(tex);
    }
        // textures
    if(main_box) SDL_DestroyTexture(main_box);
    if(bg) SDL_DestroyTexture(bg);
    if(upgrade_box) SDL_DestroyTexture(upgrade_box);
    if(leechTexture) SDL_DestroyTexture(leechTexture);
    if(playButtonTexture) SDL_DestroyTexture(playButtonTexture);
    if(quitButtonTexture) SDL_DestroyTexture(quitButtonTexture);
    if(gameTitleTexture) SDL_DestroyTexture(gameTitleTexture);
    if(menuBackgroundTexture) SDL_DestroyTexture(menuBackgroundTexture);

    // cleaning fonts
    if(standardFont) TTF_CloseFont(standardFont);
    if(smallFont) TTF_CloseFont(smallFont);
    if(bigFont) TTF_CloseFont(bigFont);

    TTF_Quit();

    // cleaning window
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);

    // cleaning music
    Mix_CloseAudio();

    SDL_Quit();
}

bool Game::running(){ // self explantory
    return isRunning;
}