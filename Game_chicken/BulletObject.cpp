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
		LoadImg("images/sphere.png", screen, 0, 255, 255);
	}

	else {
		LoadImg("images/dando.png", screen, 0, 0, 0);
	}
}


void BulletObject::HandleMove(const int& x_boder, const int& y_boder) {
	rect_.y -= y_val_;
	rect_.x += x_val_;
	if (rect_.y < 0) is_move_ = false;
}

