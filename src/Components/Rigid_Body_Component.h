#ifndef RIGID_BODY_COMPONENT_H
#define RIGID_BODY_COMPONENT_H

#include "../J2D_Defs.h"

struct Rigid_Body_Component {
	Vec2 velocity;

	Rigid_Body_Component(Vec2 vel = Vec2(0.0, 0.0))
		: velocity(vel)
	{
	}
};

#endif // !RIGID_BODY_COMPONENT_H
