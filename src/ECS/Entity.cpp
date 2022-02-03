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

void Entity::tag(const Str& tag)
{
	m_registry->tag_entity(*this, tag);
}

bool Entity::has_tag(const Str& tag) const
{
	return m_registry->entity_has_tag(*this, tag);
}

void Entity::group(const Str& group)
{
	m_registry->group_entity(*this, group);
}

bool Entity::belongs_to_group(const Str& group) const
{
	return m_registry->entity_belongs_to_group(*this, group);
}
