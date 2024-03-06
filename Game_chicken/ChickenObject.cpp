#include "ChickenObject.h"

ChickenObject::ChickenObject() {
	chicken_x_val_ = 0;
	chicken_y_val_ = 0;
	chicken_width_ = 0;
	chicken_height_ = 0;
	chicken_move_ = false;
}
ChickenObject::~ChickenObject() {

}

void ChickenObject::HandelChickenMove(const int& x_boder, const int& y_boder) {
	

	rect_.y += chicken_x_val_;
	if (rect_.y > y_boder) chicken_move_ = false;
}
void ChickenObject::LoadImgChicken(SDL_Renderer* screen) {
	LoadImg("images/Chickentype1.png", screen);
	chicken_width_ = rect_.w;
	chicken_height_ = rect_.h;
}

void ChickenObject::SetEgg(SDL_Renderer* screen) {
	EggObject* egg = new EggObject();

	egg->LoadImgEgg(screen);
	egg->SetRect(this->rect_.x + 25, rect_.y + 45);
	egg->set_egg_x_val(3);
	egg->set_egg_move(true);
	p_egg = egg;
}

void ChickenObject::HandelEgg(SDL_Renderer* screen) {
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



