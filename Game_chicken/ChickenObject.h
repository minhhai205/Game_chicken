#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"
#include "EggObject.h"

#include <vector>


#define NUM_FRAME_CHICKEN 18

class ChickenObject : public BaseObject{
public:
	 ChickenObject();
	~ChickenObject();


	void set_chicken_x_val(const int xVal) {chicken_x_val_ = xVal;}
	void set_chicken_y_val(const int yVal) {chicken_y_val_ = yVal;}

	bool get_chicken_move() const { return chicken_move_; }
	void set_chicken_move(const bool& Move) {chicken_move_ = Move;}

	void HandelChickenMove(const int& x_boder, const int& y_boder);
	void LoadImgChicken(SDL_Renderer* screen);
	
	void set_kill(int kill_) { kill = kill_; }
	int get_kill(){return kill;}

	SDL_Rect GetRectFrame();

	void SetEgg(SDL_Renderer* screen, int type);

	// Hàm xử lí bắn trứng
	void ShowEgg(SDL_Renderer* screen);

	EggObject* get_egg() const { return p_egg; }
	
	//
	void set_clip();
	void ShowChicken(SDL_Renderer* screen);
	void set_frame(const int& fr) { frame_ = fr; }
private:

	EggObject* p_egg;
	std::vector<ChickenObject*> p_chicken_list_; 
	SDL_Rect frame_clip_[NUM_FRAME_CHICKEN];
	int frame_;
	int chicken_width_; 
	int chicken_height_;
	float chicken_x_val_;
	float chicken_y_val_;
	bool chicken_move_;
	int kill;
};