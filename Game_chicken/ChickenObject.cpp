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
	//rect_.x += 1;
	//rect_.y += 1;
	/*if (check == true) {
		rect_.x += 2;
		rect_.y += 2;
		if (rect_.x + chicken_width_ >= SCREEN_WIDTH) check = false;
	}
	else if (check == false) {
		rect_.x -= 2;
		rect_.y += 2;
		if (rect_.x <= 0) check = true;
	}
	*/
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
	
	std::string path = "images//chicken.png";
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



void ChickenObject::SetEgg(SDL_Renderer* screen) {
	EggObject* egg = new EggObject();

	egg->LoadImgEgg(screen);
	egg->SetRect(this->rect_.x + 25, rect_.y + 45);
	egg->set_egg_x_val(3);
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



