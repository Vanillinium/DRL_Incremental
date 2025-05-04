#include "game.hpp"
#include "Resources.hpp"

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

void Game::upgradeLogics(){ // TODO
    if(upgrade[0]){
        CPSThreshold = 7.5;
    }
    if(upgrade[1]){
        decaySubtractAmount = 5;
    }
    if(upgrade[2]){
        dangerThreshold = 800;
        bonusMoneyMultiplier = 1;
    }
    if(upgrade[3]){
        decaySubtractAmount = 10;
    }
    if(upgrade[4]){
        CPSThreshold = 5;
        leechMax = 5;
        bonusMoneyMultiplier = 2.5;
    }
    if(upgrade[5]){
        leechSpawnInterval = 7500;
        disableMax = 20000;
    }

}

