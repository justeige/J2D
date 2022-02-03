#ifndef PROJECTILE_COMPONENT_H
#define PROJECTILE_COMPONENT_H

#include "../J2D_Defs.h"
#include <SDL.h>

struct Projectile_Component {
	bool is_friendly;
	int hit_percent_damage;
	int duration;
	u32 start_time;

	Projectile_Component(bool is_friend = false, int hit_percent_dmg = 0, int dur = 0)
		: is_friendly{is_friend}, 
	  	  hit_percent_damage{hit_percent_dmg}, 
		  duration{dur},
		  start_time{SDL_GetTicks()}
	{
	}
};

inline bool is_end_of_life(Projectile_Component projectile)
{
	return SDL_GetTicks() - projectile.start_time > projectile.duration;
}

#endif // PROJECTILE_COMPONENT_H
