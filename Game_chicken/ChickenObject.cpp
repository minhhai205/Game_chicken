#include "ChickenObject.h"

ChickenObject::ChickenObject() {
	chicken_x_val_ = 0;
	chicken_y_val_ = 0;
	chicken_width_ = 0;
	chicken_height_ = 0;
	chicken_move_ = false;

	chicken_type = CHICKEN_TYPE_1;
}
ChickenObject::~ChickenObject() {

}

void ChickenObject::HandelChickenMove(const int& x_boder, const int& y_boder) {
	

	rect_.y += chicken_x_val_;
	if (rect_.y > y_boder) chicken_move_ = false;
}
void ChickenObject::LoadImgChicken(SDL_Renderer* screen) {
	if (chicken_type == CHICKEN_TYPE_1) {
		LoadImg("images/Chickentype1.png", screen);
		chicken_width_ = rect_.w;
		chicken_height_ = rect_.h;

	}
	else {
		LoadImg("images/Chickentype2.png", screen);

		SDL_Texture* new_texture = NULL;
		std::string path = "images/Chickentype2.png";
		SDL_Surface* load_surface = IMG_Load(path.c_str());
		if (load_surface != NULL) {
			SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0x22, 0x3E, 0x4A));
			new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
			if (new_texture != NULL) {
				rect_.w = load_surface->w;
				rect_.h = load_surface->h;
			}
			SDL_FreeSurface(load_surface);
		}
		p_object_ = new_texture;

		chicken_width_ = rect_.w;
		chicken_height_ = rect_.h;
	}
}


SDL_Rect ChickenObject::GetRectFrame() {
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = rect_.w;
	rect.h = rect_.h;

	return rect;
}

void ChickenObject::SetEgg(SDL_Renderer* screen) {
	EggObject* egg = new EggObject();

	egg->LoadImgEgg(screen);
	egg->SetRect(this->rect_.x + 25, rect_.y + 45);
	egg->set_egg_x_val(3);
	egg->set_egg_move(true);
	p_egg = egg;

}

void ChickenObject::ShowEgg(SDL_Renderer* screen) {
	if (p_egg != NULL) {
		if (p_egg->get_egg_move() == true) {
			p_egg->HandleEggMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			p_egg->Render(screen);
		}
		else {
			if (p_egg != NULL) {
				delete p_egg;
				p_egg = NULL;
			}
		}
	}
}



