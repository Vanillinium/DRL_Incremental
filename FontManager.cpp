#include "FontManager.hpp"

SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor, SDL_Renderer* ren){
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,text,textColor );
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, textSurface );
    SDL_FreeSurface(textSurface);
    return texture;
}

