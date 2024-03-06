#include "EggObject.h"

EggObject::EggObject() {
	egg_x_val_ = 0;
	egg_y_val_ = 0;
    //egg_weight_ = 0;
    //egg_height_ = 0;
	egg_move_ = false;
}
EggObject::~EggObject() {

}

void EggObject::LoadImgEgg(SDL_Renderer* screen) {
    std::string path = "images/egg.png";
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL) {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0x22, 0x3E, 0x4A));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL) {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;

            //egg_weight_ = rect_.w;
            //egg_height_ = rect_.h;
        }
        SDL_FreeSurface(load_surface);
    }
    p_object_ = new_texture;
}


void EggObject::HandleEggMove(const int& x_boder, const int& y_boder) {
	rect_.y += egg_x_val_;
	if (rect_.y > y_boder) egg_move_ = false;
}

