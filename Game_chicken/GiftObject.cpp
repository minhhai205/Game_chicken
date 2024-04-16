#include "GiftObject.h"

GiftObject::GiftObject() {
	gift_x_val_ = 0;
	gift_move_ = false;
	type_gift = 0;
}

GiftObject::~GiftObject() {

}

void GiftObject::LoadImgGift(std::string path, SDL_Renderer* screen) {
    LoadImg(path, screen, 0, 0, 0);
}


void GiftObject::HandleGiftMove(const int& x_boder, const int& y_boder) {
    rect_.y += gift_x_val_;
    if (rect_.y > y_boder) gift_move_ = false;
}

