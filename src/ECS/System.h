#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

#include "Entity.h"
#include "Signature.h"

class System {
public:
	System() = default;
	~System() = default;

	void add_entity(Entity e);
	void remove_entity(Entity e);
	bool changed_flag() const;
	void clear_changed_flag();
	std::vector<Entity> system_entities() const;
	const Signature& component_signature() const;

	template <class TComponent>
	void require_component();

private:
	Signature m_component_signature;
	std::vector<Entity> m_entities;
	bool m_entities_changed = false;
};

#endif // !SYSTEM_H

