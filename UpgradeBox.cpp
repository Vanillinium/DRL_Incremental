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

        // play sfx
        Mix_PlayChannel(-1, upgradeSound, 0);

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
    if(upgrade[0]){ // FIRST UPGRADE
        // active overload debuff
        CPSThreshold = 7.5;
    }
    if(upgrade[1]){ // SECOND UPGRADE
        // active decay debuff
        decaySubtractAmount = 5;
        subtractedInterval = 1500;
    }
    if(upgrade[2]){ // THIRD UPGRADE
        // increase danger threshold
        dangerThreshold = 800;
        // active bonus 
        bonusMoneyMultiplier = 0.5;
    }
    if(upgrade[3]){ // FOURTH UPGRADE
        decaySubtractAmount = 10;
        disableMax = 10000;
    }

    if(upgrade[4]){ // FIFTH UPGRADE
        dangerThreshold = 1000;
        // active leech debuff
        leechMax = 5;
        dangerMax = 5000;
        bonusMoneyMultiplier = 1.5;
    }

    if(upgrade[5]){ // SIXTH UPGRADE
        dangerThreshold = 1000;
        leechSpawnInterval = 7500;
        disableMax = 20000;
        CPSThreshold = 5;
        leechSubtractAmount = 20;
    }

    if(upgrade[6]){ // SEVENTH UPGRADE
        dangerThreshold = 1500;
        leechMax = 10;
        leechSpawnInterval = 5000;
        decaySubtractAmount = 50;
        bonusMoneyMultiplier = 2.5;
    }

    if(upgrade[7]){ // EIGHTH UPGRADE
        dangerThreshold = 2000;
        leechSpawnInterval = 4000;
        subtractedInterval = 1000;
        leechSubtractInterval = 2500;
    }

    if(upgrade[8]){ // NINTH UPGRADE
        dangerThreshold = 3000;
        disableMax = 30000;
    }

    if(upgrade[9]){ // TENTH UPGRADE
        dangerThreshold = 5000;
        bonusMoneyMultiplier = 4;
    }

}

