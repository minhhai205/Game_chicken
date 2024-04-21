#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"
#include "EggObject.h"

#include <vector>


#define NUM_FRAME_BOSS 10

class BossObject : public BaseObject {
public:
	BossObject();
	~BossObject();


	void set_boss_x_val(const int xVal) { boss_x_val_ = xVal; }
	void set_boss_y_val(const int yVal) { boss_y_val_ = yVal; }

	void set_boss_val();
	void LoadImgBoss(SDL_Renderer* screen);

	SDL_Rect GetRectFrame();

	std::vector<EggObject*> getEggList() { return egg_list; }
	int getSizeEgglist() { return egg_list.size(); }
	EggObject* BuildEgg(SDL_Renderer* screen);

	// Hàm xử lí bắn trứng
	void ShowEgg(SDL_Renderer* screen);
	void SetEgg(SDL_Renderer* screen);
	void RemoveEgg(const int& idx);


	void set_clip();
	void ShowBoss(SDL_Renderer* screen);
	void set_frame(const int& fr) { frame_ = fr; }
private:

	std::vector<EggObject*> egg_list;
	
	SDL_Rect frame_clip_[NUM_FRAME_BOSS];
	int frame_;
	int boss_width_;
	int boss_height_;
	float boss_x_val_;
	float boss_y_val_;
	bool check_x, check_y;

};