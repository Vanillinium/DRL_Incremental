#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* ren){
    SDL_Surface* textureSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, textureSurface);
    SDL_FreeSurface(textureSurface);

    return tex;
}