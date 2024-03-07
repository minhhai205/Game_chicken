﻿#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"
#include "EggObject.h"

#include <vector>

class ChickenObject : public BaseObject{
public:
	 ChickenObject();
	~ChickenObject();


	enum ChickenType {
		CHICKEN_TYPE_1 = 30,
		CHICKEN_TYPE_2 = 31,
	};



	void set_chicken_x_val(const int xVal) {
		chicken_x_val_ = xVal;
	}
	void set_chicken_y_val(const int yVal) {
		chicken_y_val_ = yVal;
	}
	float get_chicken_x_val() { return chicken_x_val_; }
	float get_chicken_y_val() { return chicken_y_val_; }

	void set_chicken_move(const bool& Move) {
		chicken_move_ = Move;
	}

	int get_chicken_width_() { return chicken_width_; }
	int get_chicken_height_() { return chicken_height_; }

	bool get_chicken_move() const { return chicken_move_; }
	void HandelChickenMove(const int& x_border, const int& y_border);


	unsigned int getTypeChicken() const { return chicken_type; }
	void setTypeChicken(const unsigned int& chickenType) {
		chicken_type = chickenType;
	}


	void LoadImgChicken(SDL_Renderer* screen);
	
	SDL_Rect GetRectFrame();

	void SetEgg(SDL_Renderer* screen);

	// Hàm xử lí bắn trứng
	void ShowEgg(SDL_Renderer* screen);

	EggObject* get_egg() const { return p_egg; }
	

private:

	EggObject* p_egg;
	std::vector<ChickenObject*> p_chicken_list_; 
	int chicken_width_; 
	int chicken_height_;
	float chicken_x_val_;
	float chicken_y_val_;
	bool chicken_move_;


	unsigned int chicken_type;
};