#include "BossObject.h"

BossObject::BossObject() {
	boss_x_val_ = 0;
	boss_y_val_ = 0;
	boss_width_ = 0;
	boss_height_ = 0;
	check_x = true;
	check_y = true;
	frame_ = 0;
}
BossObject::~BossObject() {

}

void BossObject::set_boss_val(){
	if (check_x == true) {
		rect_.x += boss_x_val_;
		if (rect_.x + boss_width_ >= SCREEN_WIDTH) check_x = false;
	}
	else if (check_x == false) {
		rect_.x -= boss_x_val_;
		if (rect_.x <= 0) check_x = true;
	}

	if (check_y == true) {
		rect_.y += boss_y_val_;
		if (rect_.y > 200) check_y = false;
	}
	else if (check_y == false) {
		rect_.y -= boss_y_val_;
		if (rect_.y <= 10) check_y = true;
	}
}

SDL_Rect BossObject::GetRectFrame() {
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = rect_.w / NUM_FRAME_BOSS;
	rect.h = rect_.h;

	return rect;
}

void BossObject::LoadImgBoss(SDL_Renderer* screen) {
	
	LoadImg("images/boss.png", screen, 170, 170, 170);
	boss_height_ = rect_.h;
	boss_width_ = rect_.w / NUM_FRAME_BOSS;

	EggObject* egg = new EggObject();

	egg->LoadImgEgg(screen);
	egg->SetRect(this->rect_.x + 120, rect_.y + 120);
	egg->set_egg_x_val(7);
	egg->set_egg_move(true);

	egg_list.push_back(egg);

}

void BossObject::set_clip() {
	if (boss_width_ > 0 && boss_height_ > 0) {
		for (int i = 0; i < NUM_FRAME_BOSS; i++) {
			frame_clip_[i].x = i * boss_width_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = boss_width_;
			frame_clip_[i].h = boss_height_;
		}
	}
}


void BossObject::ShowBoss(SDL_Renderer* screen) {

	frame_++;
	if (frame_ >= NUM_FRAME_BOSS) frame_ = 0;


	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect render_quad = { rect_.x, rect_.y , boss_width_, boss_height_ };
	if (current_clip != NULL) {
		render_quad.w = current_clip->w;
		render_quad.h = current_clip->h;
	}
	SDL_RenderCopy(screen, p_object_, current_clip, &render_quad);
}

EggObject* BossObject::BuildEgg(SDL_Renderer* screen) {
	EggObject* egg = new EggObject();
	egg->LoadImgEgg(screen);
	egg->SetRect(rect_.x + 90, rect_.y + 90);
	egg->set_egg_x_val(10);
	egg->set_egg_move(true);
	return egg;
}

void BossObject::SetEgg(SDL_Renderer* screen) {

	if (egg_list.size() > 0) {
		EggObject* egglast = egg_list.back();
		SDL_Rect eRect = egglast->GetRect();
		if (eRect.y > 380) {
			egg_list.push_back(BuildEgg(screen));
		}
	}
	else {
		egg_list.push_back(BuildEgg(screen));
	}
	
}

void BossObject::ShowEgg(SDL_Renderer* screen) {
	for (int i = 0; i < egg_list.size(); i++) {
		EggObject* p_egg = egg_list.at(i);
		if (p_egg != NULL) {
			if (p_egg->get_egg_move() == true) {
				p_egg->HandleEggMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_egg->Render(screen);
			}
			else {
				if (p_egg != NULL) {
					egg_list.erase(egg_list.begin() + i);
					delete p_egg;
					p_egg = NULL;
				}
			}
		}
	}
}

void BossObject::RemoveEgg(const int& idx) {
	int size = egg_list.size();
	if (size > 0 && idx < size) {
		EggObject* p_egg = egg_list.at(idx);
		egg_list.erase(egg_list.begin() + idx);

		if (p_egg) {
			delete p_egg;
			p_egg = NULL;
		}
	}
}


