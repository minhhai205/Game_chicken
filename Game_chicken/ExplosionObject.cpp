﻿#include "ExplosionObject.h"

ExplosionObject::ExplosionObject() {
	frame_height_ = 0;
	frame_width_ = 0;
	frame_ = 0;
}

ExplosionObject::~ExplosionObject() {

}

bool ExplosionObject::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen, 0, 255, 255);
	if (ret) {
		frame_height_ = rect_.h;
		frame_width_ = rect_.w / NUM_FRAME_EXP;
	}

	return ret;
}

void ExplosionObject::set_clip() {
    if (frame_width_ > 0 && frame_height_ > 0) {
        for (int i = 0; i < NUM_FRAME_EXP; i++) {
            frame_clip_[i].x = i * frame_width_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = frame_width_;
            frame_clip_[i].h = frame_height_;
        }
    }
}

void ExplosionObject::Show(SDL_Renderer* screen) {
    
    
    SDL_Rect* current_clip = &frame_clip_[frame_];
    SDL_Rect render_quad = { rect_.x, rect_.y , frame_width_, frame_height_ };
    if (current_clip != NULL) {
        render_quad.w = current_clip->w;
        render_quad.h = current_clip->h;
    }
    SDL_RenderCopy(screen, p_object_, current_clip, &render_quad);
}
