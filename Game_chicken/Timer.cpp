#include "Timer.h"
#include "CommonFunc.h"

Timer::Timer() {
	start_tick_ = 0;
	pause_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;
}

Timer::~Timer() {

}

void Timer::start() {
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}

void Timer::stop() {
	is_paused_ = false;
	is_started_ = false;
}

void Timer::paused() {
	if (is_started_ == true && is_paused_ == false) {
		is_paused_ = true;
		pause_tick_ = SDL_GetTicks() - start_tick_;
	}
}

void Timer::unpaused() {
	if (is_paused_ = true) {
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - pause_tick_;
		pause_tick_ = 0;
	}
}

int Timer::get_ticks() {
	if (is_started_ = true) {
		if (is_paused_ = true) return pause_tick_;
		else return SDL_GetTicks() - start_tick_;
	}
	return 0;
}

bool Timer::is_started() {
	return is_started_;
}
bool Timer::is_paused() {
	return is_paused_;
}