#include "Entity.h"
#include "Registry.h"

void Entity::kill()
{
	m_registry->kill_entity(*this);
}

Entity& Entity::operator =(const Entity& other)
{
	m_id = other.id();
	return *this;
}

bool Entity::operator == (const Entity& other) const
{
	return m_id == other.id();
}

bool Entity::operator != (const Entity& other) const
{
	return m_id != other.id();
}

bool Entity::operator < (const Entity& other) const
{
	return m_id < other.id();
}

bool Entity::operator > (const Entity& other) const
{
	return m_id > other.id();
}