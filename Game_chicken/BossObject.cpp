#include "BossObject.h"

BossObject::BossObject() {
	boss_x_val_ = 0;
	boss_y_val_ = 0;
	boss_width_ = 0;
	boss_height_ = 0;
	check = true;
	frame_ = 0;

}
BossObject::~BossObject() {

}

void BossObject::set_boss_val(){
	if (check == true) {
		rect_.x += boss_x_val_;
		if (rect_.x + boss_width_ >= SCREEN_WIDTH) check = false;
	}
	else if (check == false) {
		rect_.x -= boss_x_val_;
		if (rect_.x <= 0) check = true;
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

	std::string path = "images/boss.png";
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL) {
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 170, 170, 170));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL) {
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object_ = new_texture;

	boss_height_ = rect_.h;
	boss_width_ = rect_.w / NUM_FRAME_BOSS;


	//
	EggObject* egg = new EggObject();

	egg->LoadImgEgg(screen);
	egg->SetRect(this->rect_.x + 120, rect_.y + 120);
	egg->set_egg_x_val(4);
	egg->set_egg_move(true);

	egg_list.push_back(egg);

}

void BossObject::set_clip() {
	// Thiết lập các clip cho từng frame
	if (boss_width_ > 0 && boss_height_ > 0) {
		// Thiết lập thông số cho từng frame
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



void BossObject::SetEgg(SDL_Renderer* screen) {
	EggObject* egg = new EggObject();
	egg->LoadImgEgg(screen);
	egg->SetRect(this->rect_.x + 90, rect_.y + 90);
	egg->set_egg_x_val(4);
	egg->set_egg_move(true);

	if (egg_list.size() > 0) {
		EggObject* egglast = egg_list.back();
		SDL_Rect eRect = egglast->GetRect();
		if (eRect.y > 250) {
			egg_list.push_back(egg);

		}
	}
	else egg_list.push_back(egg);
	
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


