#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "../ECS/ECS.h"

class Event_Bus;
struct Collision_Event;

class Movement_System : public System {
public:

	Movement_System();

	void update(double delta_time);
	void subscribe_to_events(Unique<Event_Bus>& event_bus);
	void on_collision(Collision_Event& e);
};


#endif // MOVEMENT_SYSTEM_H