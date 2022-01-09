#ifndef COLLISION_EVENT_H
#define COLLISION_EVENT_H

#include "../ECS/Entity.h"
#include "../Event_Bus/Event.h"

struct Collision_Event : public Event {
	Entity a;
	Entity b;

	Collision_Event(Entity a, Entity b) : a{a}, b{b}
	{}
	
};

#endif // !COLLISION_EVENT_H
