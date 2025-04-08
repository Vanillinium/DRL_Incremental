#pragma once

#include "game.hpp"

class FontManager{
public:
    static TTF_Font* LoadFont(const std::string& filePath, int fontSize);
    static SDL_Texture* RenderText(const std::string &text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer, SDL_Rect &textRect, int height);
    static vector<SDL_Texture*> RenderMultilineText(const std::string &text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, vector<SDL_Rect> &textRects, int startingHeight);
};