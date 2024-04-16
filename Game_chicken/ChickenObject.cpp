#include "ChickenObject.h"

ChickenObject::ChickenObject() {
	chicken_x_val_ = 0;
	chicken_y_val_ = 0;
	chicken_width_ = 0;
	chicken_height_ = 0;
	chicken_move_ = false;
	frame_ = 0;
}
ChickenObject::~ChickenObject() {

}


void ChickenObject::HandelChickenMove(const int& x_boder, const int& y_boder) {

	rect_.y += chicken_x_val_;
	if (rect_.y > y_boder) chicken_move_ = false;
}

SDL_Rect ChickenObject::GetRectFrame() {
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = rect_.w / NUM_FRAME_CHICKEN;
	rect.h = rect_.h;

	return rect;
}

void ChickenObject::LoadImgChicken(SDL_Renderer* screen) {
	
	LoadImg("images//chicken.png", screen, 170, 170, 170);

	chicken_height_ = rect_.h;
	chicken_width_ = rect_.w / NUM_FRAME_CHICKEN;


}

void ChickenObject::set_clip() {
	// Thiết lập các clip cho từng frame
	if (chicken_width_ > 0 && chicken_height_ > 0) {
		// Thiết lập thông số cho từng frame
		for (int i = 0; i < NUM_FRAME_CHICKEN; i++) {
			frame_clip_[i].x = i * chicken_width_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = chicken_width_;
			frame_clip_[i].h = chicken_height_;
		}
	}
}


void ChickenObject::ShowChicken(SDL_Renderer* screen) {
	
	frame_++;
	if (frame_ >= NUM_FRAME_CHICKEN) frame_ = 0;
	

	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect render_quad = { rect_.x, rect_.y , chicken_width_, chicken_height_ };
	if (current_clip != NULL) {
		render_quad.w = current_clip->w;
		render_quad.h = current_clip->h;
	}
	SDL_RenderCopy(screen, p_object_, current_clip, &render_quad);
}



void ChickenObject::SetEgg(SDL_Renderer* screen, int type) {
	EggObject* egg = new EggObject();

	egg->LoadImgEgg(screen);
	egg->SetRect(this->rect_.x + 25, rect_.y + 45);
	if (type % 2 == 0) egg->set_egg_x_val(4);
	else egg->set_egg_x_val(5);
	egg->set_egg_move(true);
	p_egg = egg;

}

void ChickenObject::ShowEgg(SDL_Renderer* screen) {
	if (p_egg != NULL) {
		if (p_egg->get_egg_move() == true) {
			p_egg->HandleEggMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			p_egg->Render(screen);
		}
		else {
			if (p_egg != NULL) {
				delete p_egg;
				p_egg = NULL;
			}
		}
	}
}



