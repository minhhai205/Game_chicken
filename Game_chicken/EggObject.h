#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"

class EggObject : public BaseObject {
public:
	EggObject();
	~EggObject();

	enum EggType {
		EGG_SMALL = 20,
		EGG_BIG = 21,
	};

	void set_egg_x_val(const int xVal) { egg_x_val_ = xVal; }
	void set_egg_y_val(const int yVal) { egg_y_val_ = yVal; }

	void set_egg_move(const bool& Move) { egg_move_ = Move; }
	bool get_egg_move() const { return egg_move_; }
	void HandleEggMove(const int& x_border, const int& y_border);

	void LoadImgEgg(SDL_Renderer* screen);

private:

	int egg_x_val_;
	int egg_y_val_;
	bool egg_move_;
};