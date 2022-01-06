#include "System.h"

void System::add_entity(Entity e)
{
	entities.push_back(e);
	m_entities_changed = true;
}

void System::remove_entity(Entity e)
{
	// removing elements from a vector is such a shitshow in C++
	entities.erase(
		std::remove_if(
			std::begin(entities),
			std::end(entities),
			[=](Entity other) {
		return e == other;
	}
	));
	m_entities_changed = true;
}

bool System::changed_flag() const
{
	return m_entities_changed;
}

void System::clear_changed_flag()
{
	m_entities_changed = false;
}

std::vector<Entity> System::system_entities() const
{
	return entities;
}

const Signature& System::component_signature() const
{
	return m_component_signature;
}