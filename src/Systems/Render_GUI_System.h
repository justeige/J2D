#pragma once

// TODO..

#include "../ECS/ECS.h"
#include "../J2D_Defs.h"

class Render_GUI_System : public System {
public:
	Render_GUI_System() = default;

	void update(Unique<Registry>& registry);

};
