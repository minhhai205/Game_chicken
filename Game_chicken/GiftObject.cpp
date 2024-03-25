#include "GiftObject.h"

GiftObject::GiftObject() {
	gift_x_val_ = 0;
	gift_move_ = false;
	type_gift = 0;
}

GiftObject::~GiftObject() {

}

void GiftObject::LoadImgGift(SDL_Renderer* screen) {

    std::string path = "images/duiga.png";
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL) {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0, 0, 0));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL) {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;

        }
        SDL_FreeSurface(load_surface);
    }
    p_object_ = new_texture;


}


void GiftObject::HandleGiftMove(const int& x_boder, const int& y_boder) {
    rect_.y += gift_x_val_;
    if (rect_.y > y_boder) gift_move_ = false;
}

