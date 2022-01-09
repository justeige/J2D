#include "Damage_System.h"

#include "../Components/Box_Collider_Component.h"
#include "../Event_Bus/Event_Bus.h"
#include "../Events/Collision_Event.h"
#include "../Logger.h"

Damage_System::Damage_System()
{
	require_component<Box_Collider_Component>();
}

void Damage_System::subscribe_to_events(Unique<Event_Bus>& event_bus)
{
	event_bus->subscribe_to_event<Collision_Event>(this, &Damage_System::on_collision);
}

void Damage_System::on_collision(Collision_Event& e)
{
	Logger::log("collision happend!");
	e.a.kill();
	e.b.kill();
}
