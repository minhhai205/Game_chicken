#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"


class GiftObject : public BaseObject {
public:
	GiftObject();
	~GiftObject();


	void set_gift_x_val(const int xVal) { gift_x_val_ = xVal; }

	bool get_gift_move() const { return gift_move_; }
	void set_gift_move(const bool& Move) { gift_move_ = Move; }

	void HandleGiftMove(const int& x_boder, const int& y_boder);
	void LoadImgGift(SDL_Renderer* screen);

	SDL_Rect GetRectFrame();

private:
	float gift_x_val_;
	bool gift_move_;
	int type_gift;
};