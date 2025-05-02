#include "game.hpp"
#include "FontManager.hpp"
#include "Resources.hpp"

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