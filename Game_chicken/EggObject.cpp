#include "EggObject.h"

EggObject::EggObject() {
	egg_x_val_ = 0;
	egg_y_val_ = 0;
	egg_move_ = false;
    
}
EggObject::~EggObject() {

}

void EggObject::LoadImgEgg(SDL_Renderer* screen) {
    
    LoadImg("images/egg.png", screen, 34, 62, 74);
    
}


void EggObject::HandleEggMove(const int& x_boder, const int& y_boder) {
	rect_.y += egg_x_val_;
	if (rect_.y > y_boder) egg_move_ = false;
}

