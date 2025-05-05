#include "AudioManager.hpp"

void AudioManager::playBGMForState(GameState state) {
    if (state == currentMusicState && Mix_PlayingMusic()) return;  

    Mix_HaltMusic();

    switch(state) {
        case MENU:
            Mix_PlayMusic(menuMusic, -1);
            break;
        case PLAYING:
            Mix_PlayMusic(bgMusic, -1);
            break;
        case GAME_OVER:
            Mix_PlayMusic(gameOverMusic, 0);
            break;
        case WIN:
            Mix_PlayMusic(winMusic, 0);
            break;
        default:
            break;
    }

    currentMusicState = state;
}