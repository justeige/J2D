#ifndef DAMAGE_SYSTEM_H
#define DAMAGE_SYSTEM_H

#include "../J2D_Defs.h"
#include "../ECS/ECS.h"

class  Event_Bus;
struct Collision_Event;

class Damage_System : public System {
public:
	Damage_System();

	void subscribe_to_events(Unique<Event_Bus>& event_bus);

	void on_collision(Collision_Event& e);
};


#endif // !DAMAGE_SYSTEM_H

