#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"

class BulletObject : public BaseObject {
public:
	BulletObject();
	~BulletObject();

	enum BulletType {
		BLUE_BULLET = 10,
		FIRE_BULLET = 11,
	};

	void set_x_val(const int xVal) {x_val_ = xVal;}
	void set_y_val(const int yVal) {y_val_ = yVal;}

	void set_is_move(const bool& Move) {is_move_ = Move;}
	bool get_is_move() const { return is_move_; }
	void HandleMove(const int& x_border, const int& y_border);

	void set_bullet_type(const unsigned int& bulletType) {bullet_type_ = bulletType;}

	unsigned int get_bullet_type() const { return bullet_type_; }

	void LoadImgBullet(SDL_Renderer* screen);
private:
	unsigned int bullet_type_;
	int x_val_;
	int y_val_;
	bool is_move_;
};