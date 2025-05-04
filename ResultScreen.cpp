#include "game.hpp"
#include "FontManager.hpp"
#include "Resources.hpp"

void Game::gameOver(Uint32 now){
    
    if(money < dangerThreshold){
        if(!inDanger){
            inDanger = true;
            dangerStart = now;

            if(randomTextTexture) SDL_DestroyTexture(randomTextTexture);
            randomTextTexture = FontManager::RenderText("In danger.", bigFont, textColor, renderer, randomTextRect, 250);
        }
        
        if(now - dangerStart >= dangerMax){
            currentGameState = GAME_OVER;
            resultEnterTime = now;
        }
    }

    else{
        dangerStart = 0;
        inDanger = false;
    }
}

void Game::gameWin(Uint32 now){
    if(money >= 20000){
        currentGameState = WIN;
        resultEnterTime = now;
    }
}