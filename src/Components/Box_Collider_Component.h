#ifndef BOX_COLLIDER_COMPONENT_H
#define BOX_COLLIDER_COMPONENT_H

#include "../J2D_Defs.h"

struct Box_Collider_Component {
	int width;
	int height;
	Vec2 offset;

	Box_Collider_Component(int w = 0, int h = 0, Vec2 offset = Vec2{0})
		: width{w}, height{h}, offset{offset}
	{}
};

#endif // !BOX_COLLIDER_COMPONENT_H

