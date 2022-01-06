#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <SDL.h>

struct Animation_Component {
	int num_frames;
	int current_frame;
	int frame_rate_speed;
	bool should_loop;
	Uint32 start_time;

	Animation_Component(int n_frames = 1, int frame_rate_speed = 1, bool should_loop = true) : current_frame{1}, num_frames{n_frames}, frame_rate_speed{frame_rate_speed}, should_loop{should_loop}, start_time{SDL_GetTicks()}
	{}
};

#endif // ANIMATION_COMPONENT_H

