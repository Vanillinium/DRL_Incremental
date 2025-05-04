#include "game.hpp"
#include "Resources.hpp"


// MAIN MECHANICS
void Game::decay(Uint32 now){

    if(now - subtractedStart >= subtractedInterval){
        cout << "[decay] Decaying..." << endl;

        money -= decaySubtractAmount;
        displayed_DRL = (double) money / 10;

        updateMoneyText();

        subtractedStart = now;
    }
}

void Game::forceDisable(Uint32 now){
    if(!forceClickingDisabled){
        cout << "[overloadChecker] Disabled!" << endl;
        forceClickingDisabled = true;
        disableStart = SDL_GetTicks();

        announcementText = "Overloaded!\nClicking disabled.";

        reloadAnnouncementText();
    }
}

void Game::updateForceDisable(Uint32 now){
    if(forceClickingDisabled && now - disableStart >= disableMax){
        cout << "[overloadChecker] Re-enabled!" << endl;
        forceClickingDisabled = false;
        naturalDecay = true;
        announcementText = "Clicking re-enabled!";
        reloadAnnouncementText();
    }
}

void Game::overload(Uint32 now){

    if(now - clickCounterStart >= clickCounterInterval){
        CPS = (double) clickCounter / (double) (now - clickCounterStart) * 1000;

        if(CPS >= CPSThreshold && !forceClickingDisabled){
            forceDisable(now);

            decay(now);
            naturalDecay = false;
        }
        clickCounterStart = now;
        cout << "[overloadChecker] CPS : " << CPS << endl;
        clickCounter = 0;
    }
}

void Game::leechSpawn(){
    // SPAWNS A LEECH
    if(leechCount >= leechMax) return;

    SDL_Rect leechNew;
    bool isPosValid = false;

    for(int i = 0; i < 100 && !isPosValid; i++){
        leechNew = {rand() % (WIDTH - 32), rand() % (HEIGHT - 32), 32, 32};

        if (!SDL_HasIntersection(&leechNew, &rect_main_box) &&
            !SDL_HasIntersection(&leechNew, &rect_upgrade_box)){
            isPosValid = true;
        }   
    }

    if(isPosValid){
        leechRects.push_back(leechNew);
        leechCount++;
    }
    
}

void Game::leechUpdate(Uint32 now){
    // SPAWNING
    if(now - leechSpawnStart >= leechSpawnInterval && leechCount < leechMax){
        leechSpawn();

        cout << "[leechChecker] Leech spawned!" << endl;
        cout << "[leechChecker] Leech count: " << leechCount << endl;

        leechSpawnStart = now;
    }

    // LEECHING
    if(now - leechSubtractStart >= leechSubtractInterval && leechCount > 0){
        
        money -= leechSubtractAmount * leechCount;
        displayed_DRL = (double) money / 10;

        updateMoneyText();

        leechSubtractStart = now;
    }
    else if(leechCount == 0){
        leechSubtractStart = now;
    }
}

void Game::bonusMoney(Uint32 now){

    if(now - bonusMoneyStart >= bonusMoneyInterval){

        MPS = (double) moneyCounter / (double) (now - bonusMoneyStart) * 1000;

        money += (int) MPS * bonusMoneyMultiplier;
        displayed_DRL = (double) money / 10;
        updateMoneyText();

        cout << "[bonusMoney] MPS : " << MPS << " | DRL/s : " << (int) MPS / 10 << endl;

        bonusMoneyStart = now;

        moneyCounter = 0;
    }
}