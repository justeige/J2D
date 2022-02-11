#ifndef REGISTRY_IMPL_H
#define REGISTRY_IMPL_H

#include <string>

#include "Component.h"

//#include "../Logger.h"


template <class T, class ...TArgs>
void Registry::add_component(Entity e, TArgs&& ...args)
{
	const auto component_id = Component<T>::id();
	const auto entity_id = e.id();

	if (component_id >= m_component_pools.size()) {
		m_component_pools.resize(component_id + 1, nullptr);
	}

	if (!m_component_pools[component_id]) {
		m_component_pools[component_id] = std::make_shared<Object_Pool<T>>();
	}

	auto component_pool = std::static_pointer_cast<Object_Pool<T>>(m_component_pools[component_id]);

	T new_component(std::forward<TArgs>(args)...);

	component_pool->set(entity_id, new_component);

	m_entity_component_signatures[entity_id].set(component_id);

	//Logger::log("Component id = " + std::to_string(component_id) + " was added to entity id " + std::to_string(entity_id));
}

template <class T>
void Registry::remove_component(Entity e)
{
	const auto component_id = Component<T>::id();
	const auto entity_id = e.id();

	auto component_pool = std::static_pointer_cast<Object_Pool<T>>(m_component_pools[component_id]);
	component_pool->remove(entity_id);

	m_entity_component_signatures[entity_id].set(component_id, false);
}

template <class T>
bool Registry::has_component(Entity e)
{
	const auto component_id = Component<T>::id();
	const auto entity_id = e.id();

	return m_entity_component_signatures[entity_id].test(component_id);
}

template <class T>
T& Registry::component(Entity e) const
{
	const auto component_id = Component<T>::id();
	const auto entity_id = e.id();

	auto component_pool = std::static_pointer_cast<Object_Pool<T>>(m_component_pools[component_id]);
	return component_pool->get(entity_id);
}

template <class TSystem, class ...TArgs>
void Registry::add_system(TArgs&& ...args)
{
	auto new_system = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
	m_systems.insert(std::make_pair(std::type_index(typeid(TSystem)), new_system));
}

template <class TSystem>
void Registry::remove_system()
{
	auto system = m_systems.find(std::type_index(typeid(TSystem)));
	m_systems.erase(system);
}

template <class TSystem>
bool Registry::has_system() const
{
	return contains(m_systems, std::type_index(typeid(TSystem)));
}

template <class TSystem>
TSystem& Registry::system() const
{
	auto system = m_systems.find(std::type_index(typeid(TSystem)));
	return *std::static_pointer_cast<TSystem>(system->second);
}

#endif // !REGISTRY_IMPL_H

