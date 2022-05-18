#include "imptimer.h"


ImpTimer::ImpTimer() {
	start_tick_ = 0;
	paused_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;
}


void ImpTimer::Start() {
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}

void ImpTimer::Stop() {
	is_paused_ = false;
	is_started_ = false;

}

void ImpTimer::Paused() {
	if (is_started_ == true && is_paused_ == false) {
		is_paused_ = true;
		paused_tick_ = SDL_GetTicks();
	}
}

void ImpTimer::Unpaused() {
	if (is_paused_ == true) {
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - paused_tick_;
		paused_tick_ = 0;
	}
}

int ImpTimer::Get_ticks() {
	if (is_started_ == true) {
		if (is_paused_ == true) {
			return paused_tick_;
		}
		else { return SDL_GetTicks() - start_tick_;
		}
	}
	return 0;
}


bool ImpTimer::Is_started() {
	return is_started_;
}

bool ImpTimer::Is_paused() {
	return is_paused_;
}