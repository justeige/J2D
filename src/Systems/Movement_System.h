#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "../ECS/ECS.h"


class Movement_System : public System {
public:

	Movement_System();

	void update(double delta_time);
};


#endif // MOVEMENT_SYSTEM_H