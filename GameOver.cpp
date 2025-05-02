#include "game.hpp"
#include "FontManager.hpp"
#include "Resources.hpp"

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