#include "FontManager.hpp"
#include "Resources.hpp"

TTF_Font *FontManager::LoadFont(const std::string &filePath, int fontSize){
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
    return font;
}

SDL_Texture *FontManager::RenderText(const std::string &text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer, SDL_Rect &textRect, int height){
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    TTF_SizeText(font, text.c_str(), &textRect.w, &textRect.h);

    textRect.x = (WIDTH - textRect.w) / 2;  
    textRect.y = height;  // TODO: CUSTOMIZABLE LOCATION

    SDL_FreeSurface(textSurface);

    return textTexture;
}

// THIS CODE HAS BEEN WRITTEN BY CHATGPT.
// PURPOSE: MAKE A MULTILINE TEXT SYSTEM
// USED FOR ANNOUNCEMENT.
vector<SDL_Texture*> FontManager::RenderMultilineText(const std::string &text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, vector<SDL_Rect> &textRects, int startingHeight) {
    vector<SDL_Texture*> textTextures;
    textRects.clear(); // Xóa danh sách cũ

    stringstream ss(text);
    string line;
    int yOffset = 0;

    while (getline(ss, line, '\n')) {  // Cắt text theo ký tự xuống dòng '\n'
        SDL_Rect textRect;
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, line.c_str(), color);
        if (!textSurface) continue;

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        TTF_SizeText(font, line.c_str(), &textRect.w, &textRect.h);
        SDL_FreeSurface(textSurface);

        // **🔥 Căn giữa từng dòng**
        textRect.x = (WIDTH - textRect.w) / 2;
        textRect.y = startingHeight + yOffset;  // Các dòng tiếp theo sẽ xuống dưới
        yOffset += textRect.h + 5;  // Khoảng cách giữa các dòng

        textTextures.push_back(textTexture);
        textRects.push_back(textRect);
    }

    return textTextures;
}