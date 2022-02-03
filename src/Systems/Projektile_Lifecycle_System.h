#pragma once

// TODO split

#include "../ECS/ECS.h"

#include "../Components/Projectile_Component.h"

class Projectile_Lifecycle_System : public System {
public:
	Projectile_Lifecycle_System()
	{
		require_component<Projectile_Component>();
	}

	void update()
	{
		for (auto entity : system_entities()) {
			auto projectile = entity.component<Projectile_Component>();

			if (is_end_of_life(projectile)) {
				entity.kill();
			}
		}
	}
};
