#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

struct Health_Component {
	int health_percentage;

	Health_Component(int hp_percent = 0)
		: health_percentage{hp_percent}
	{
	}
};

#endif // HEALTH_COMPONENT_H
