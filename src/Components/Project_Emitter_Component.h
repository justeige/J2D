#ifndef PROJECT_EMITTER_COMPONENT_H
#define PROJECT_EMITTER_COMPONENT_H

#include "../J2D_Defs.h"

struct Projectile_Emitter_Component {
	Vec2 projectile_velocity;
	int repeat_frequency;
	int projectile_duration;
	int hit_percentage_dmg;
	bool is_friendly;
	u32 last_emission_time;

	Projectile_Emitter_Component(Vec2 projectile_vel = Vec2{0},
							  int repeat_freq = 0,
							  int projectile_dur = 10000,
							  int hit_percent_dmg = 10,
							  bool is_friendly = false)
		: projectile_velocity{projectile_vel},
		  repeat_frequency{repeat_freq},
		  projectile_duration{projectile_dur},
		  hit_percentage_dmg{hit_percent_dmg},
		  is_friendly{is_friendly},
		  last_emission_time{SDL_GetTicks()}
	{
	}
};

inline bool time_to_emit_new_projectile(const Projectile_Emitter_Component& projectile)
{
	return SDL_GetTicks() - projectile.last_emission_time > projectile.repeat_frequency;
}

#endif // !PROJECT_EMITTER_COMPONENT_H