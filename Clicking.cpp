#include "game.hpp"
#include "Resources.hpp"

void Game::clickedInBoxCheckCondition(){
    if(isMainBoxClicked){
        money += increment[incrementIndex];
        displayed_DRL = (double) money / 10;

        updateMoneyText();

        // reset idle counter when clicked
        idleTime = SDL_GetTicks();

        // increase clicking counter
        clickCounter++;
        
        // adding in bonus money counter 
        moneyCounter += increment[incrementIndex];

        // reset clicking cond
        isMainBoxClicked = false;
    }
}