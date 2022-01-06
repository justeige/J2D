#include "Movement_System.h"

#include "../Components/Transform_Component.h"
#include "../Components/Rigid_Body_Component.h"

Movement_System::Movement_System()
{
	require_component<Transform_Component>();
	require_component<Rigid_Body_Component>();
}

void Movement_System::update(double delta_time)
{
	for (auto e : system_entities()) {
		auto& transform = e.component<Transform_Component>();
		const auto rigid_body = e.component<Rigid_Body_Component>();

		transform.position.x += rigid_body.velocity.x * delta_time;
		transform.position.y += rigid_body.velocity.y * delta_time;
	}
}