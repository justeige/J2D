#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "../ECS/ECS.h"

class Event_Bus;

class Collision_System : public System {
public:
	Collision_System();

	void update(Unique<Event_Bus>& event_bus);
};

#endif // COLLISION_SYSTEM_H
