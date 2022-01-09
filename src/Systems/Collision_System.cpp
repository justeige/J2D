#include "Collision_System.h"

#include "../Components/Components.h"
#include "../Event_Bus/Event_Bus.h"
#include "../Events/Collision_Event.h"
#include "../Logger.h"


bool AABB(double ax, double ay, double aw, double ah, double bx, double by, double bw, double bh)
{
	return
		ax < bx + bw &&
		ay < by + bh &&
		ax + aw > bx &&
		ay + ah > by;
}

bool AABB(SDL_Rect a, SDL_Rect b)
{
	return AABB(a.x, a.y, a.w, a.h, b.x, b.y, b.w, b.h);
}

Collision_System::Collision_System()
{
	require_component<Box_Collider_Component>();
	require_component<Transform_Component>();
}

void Collision_System::update(Unique<Event_Bus>& event_bus)
{
	// go through all entitites once and perform an AABB check
	auto entities = system_entities();

	for (auto it1 = entities.begin(); it1 != entities.end(); ++it1) {
		auto a = *it1;
		auto a_rect = create_rect_from(
			a.component<Transform_Component>(),
			a.component<Box_Collider_Component>()
		);

		for (auto it2 = it1; it2 != entities.end(); ++it2) {
			auto b = *it2;

			if (a == b) {
				continue; // entities can't collide with themselves
			}

			auto b_rect = create_rect_from(
				b.component<Transform_Component>(),
				b.component<Box_Collider_Component>()
			);

			if (AABB(a_rect, b_rect)) {
				event_bus->emit<Collision_Event>(a, b);
			}
		}
	}
}
