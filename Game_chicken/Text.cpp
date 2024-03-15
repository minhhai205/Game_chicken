#include "Text.h"

Text::Text() {
    
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
    texture = NULL;
}
Text::~Text() {

}



void Text::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
    text_color.r = red;
    text_color.g = green;
    text_color.b = blue;
}

void Text::SetColor(int type) {
    SDL_Color color;
    if (type == WHITE) color = { 255, 255, 255 };
    else if (type == RED) color = { 255, 0, 0 };
    else if (type == BLACK) color = { 0, 0, 0 };
    text_color = color;
}

bool Text::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
    if (text_surface) {
        texture = SDL_CreateTextureFromSurface(screen, text_surface);
        wight = text_surface->w;
        height = text_surface->h;
        SDL_FreeSurface(text_surface);
    }

    return !texture;
}

void Text::Free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void Text::RenderText(SDL_Renderer* screen,
    int xp, int yp,
    SDL_Rect* clip ,
    double angle,
    SDL_Point* center ,
    SDL_RendererFlip flip) {
    SDL_Rect render = { xp, yp, wight, height };
    if (clip != NULL) {
        render.w = clip->w;
        render.h = clip->h;
    }
    SDL_RenderCopyEx(screen, texture, clip, &render, angle, center, flip);
}