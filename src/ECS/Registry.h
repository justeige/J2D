#ifndef REGISTRY_H
#define REGISTRY_H

#include <JUL/Container.h>
#include <JUL/Pointer.h>
using namespace jul;

#include <typeindex>

#include "Signature.h"
#include "System.h"
#include "Object_Pool.h"
#include "Entity.h"

class Registry {
public:

	// ---------------------
	// Manage entities
	// ---------------------

	Entity create_entity();
	void kill_entity(Entity e);
	void update_entities();
	void add_entity_to_systems(Entity e);
	void remove_entity_from_systems(Entity e);


	// ---------------------
	// Manage components
	// ---------------------

	template <class T, class ...TArgs>
	void add_component(Entity e, TArgs&& ...args);

	template <class T>
	void remove_component(Entity e);

	template <class T>
	bool has_component(Entity e);

	template <class T>
	T& component(Entity e) const;



	// ---------------------
	// Manage systems
	// ---------------------

	template <class TSystem, class ...TArgs>
	void add_system(TArgs&& ...args);

	template <class TSystem>
	void remove_system();

	template <class TSystem>
	bool has_system() const;

	template <class TSystem>
	TSystem& system() const;

private:
	int            m_num_entities = 0;
	Deq<int>       m_free_ids;
	Set<Entity>    m_entities_to_be_added;
	Set<Entity>    m_entities_to_be_removed;
	Vec<Signature> m_entity_component_signatures;
	Vec<Shared<Object_Pool_Base>>         m_component_pools;
	UMap<std::type_index, Shared<System>> m_systems;
};

#endif // REGISTRY_H
