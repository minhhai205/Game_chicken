#include "BulletObject.h"

BulletObject::BulletObject() {
	x_val_ = 0;
	y_val_ = 0;
	bullet_type_ = RED_BULLET;
	is_move_ = false;
}
BulletObject::~BulletObject() {

}

void BulletObject::LoadImgBullet(SDL_Renderer* screen) {
	if (bullet_type_ == RED_BULLET) {
		LoadImg("images/sphere.png", screen);
	}

	else {
		std::string path = "images/dando.png";
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
}


void BulletObject::HandleMove(const int& x_boder, const int& y_boder) {
	//rect_.x += x_val_;
	rect_.y -= x_val_;
	//if (rect_.x > x_boder) is_move_ = false;
	if (rect_.y < 0) is_move_ = false;
}

