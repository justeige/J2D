#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include "../ECS/ECS.h"

class Animation_System : public System {
public:
	Animation_System();
	
	void update();
};

#endif // ANIMATION_SYSTEM_H

