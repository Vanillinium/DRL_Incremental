#include "game.hpp"
#include "Resources.hpp"
// MAIN MECHANICS
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
        naturalDecay = true;
        announcementText = "Clicking re-enabled!";
        reloadAnnouncementText();
    }
}

void Game::overload(Uint32 now){

    if(now - counterStart >= counterInterval){
        CPS = (double) clickCounter / (double) (now - counterStart) * 1000;

        if(CPS >= CPSThreshold && !forceClickingDisabled){
            forceDisable(now);

            decay(now);
            naturalDecay = false;
        }
        counterStart = now;
        cout << "[overloadChecker] CPS : " << CPS << endl;
        clickCounter = 0;
    }
}