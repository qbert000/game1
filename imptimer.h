#pragma once

#include "commonFunc.h"

class ImpTimer {
public:
	ImpTimer();

	void Start();
	void Stop();
	void Paused();
	void Unpaused();

	int Get_ticks();

	bool Is_started();
	bool Is_paused();

private:
	int start_tick_;
	int paused_tick_;

	bool is_paused_;
	bool is_started_;
};
