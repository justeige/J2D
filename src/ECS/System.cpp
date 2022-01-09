#include "System.h"

void System::add_entity(Entity e)
{
	m_entities.push_back(e);
	m_entities_changed = true;
}

void System::remove_entity(Entity e)
{
	// removing elements from a vector is such a shitshow in C++
	m_entities.erase(
		std::remove_if(
			std::begin(m_entities),
			std::end(m_entities),
			[=](Entity other) {
				return e.id() == other.id();
		}),
		std::end(m_entities)
	);
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
	return m_entities;
}

const Signature& System::component_signature() const
{
	return m_component_signature;
}