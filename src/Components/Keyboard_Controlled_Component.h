#pragma once

// TODO fix guards

#include "../J2D_Defs.h"

struct Keyboard_Controlled_Component {
	Vec2 up_velocity;
	Vec2 right_velocity;
	Vec2 down_velocity;
	Vec2 left_velocity;


	Keyboard_Controlled_Component(Vec2 up_vel = Vec2{0},
		                          Vec2 right_vel = Vec2{ 0 },
								  Vec2 down_vel = Vec2{ 0 },
							      Vec2 left_vel = Vec2{ 0 })
		: up_velocity{ up_vel }, 
		  right_velocity{ right_vel }, 
		  down_velocity{ down_vel },
		  left_velocity {left_vel}
	{
	}

};
