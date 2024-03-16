#include "HealthPlayer.h"

HealthPlayer::HealthPlayer() {

}

HealthPlayer::~HealthPlayer() {

}

void HealthPlayer::AddPos(const int& xpos) {
	pos_list_.push_back(xpos);
}
void HealthPlayer::LoadHealth(SDL_Renderer* screen) {
	if (number_ == pos_list_.size()) {
		for (int i = 0; i < pos_list_.size(); i++) {
			rect_.x = pos_list_.at(i);

			SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h };

			SDL_RenderCopy(screen, p_object_, NULL, &renderQuad);
		}
	}
}

void HealthPlayer::Init(SDL_Renderer* screen) {
	LoadImg("images/health.png", screen);
	number_ = 3;
	if (pos_list_.size() > 0) {
		pos_list_.clear();
	}
	AddPos(10);
	AddPos(30);
	AddPos(50);

}

void HealthPlayer::ResetHealth() {
	number_ = 3;
	if (pos_list_.size() > 0) {
		pos_list_.clear();
	}
	AddPos(10);
	AddPos(30);
	AddPos(50);
}
void HealthPlayer::Decrease() {
	--number_;
	pos_list_.pop_back();
}