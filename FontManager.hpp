#pragma once

#include "game.hpp"

class FontManager{
    public:
        static TTF_Font* LoadFont(const char* path, int size){
            TTF_Font* gFont = TTF_OpenFont(path, size );
        }
};