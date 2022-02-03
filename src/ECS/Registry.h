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



	// ---------------------
	// Tag managment
	// ---------------------
	void   tag_entity(Entity e, const Str& tag);
	bool   entity_has_tag(Entity e, const Str& tag) const;
	Entity entity_by_tag(const Str& tag)  const;
	void   remove_entity_tag(Entity e);



	// ---------------------
	// Group managment
	// ---------------------
	void group_entity(Entity e, const Str& group);
	bool entity_belongs_to_group(Entity e, const Str& group) const;
	Vec<Entity> entities_by_group(const Str& group)  const;
	void        remove_entity_from_group(Entity e);


private:
	int            m_num_entities = 0;
	Deq<int>       m_free_ids;
	Set<Entity>    m_entities_to_be_added;
	Set<Entity>    m_entities_to_be_removed;
	Vec<Signature> m_entity_component_signatures;
	Vec<Shared<Object_Pool_Base>>         m_component_pools;
	UMap<std::type_index, Shared<System>> m_systems;

	// grouping and tagging
	UMap<Str, Entity>      m_entity_per_tag;
	UMap<int, Str>         m_tag_per_entity;
	UMap<Str, Set<Entity>> m_entities_per_group;
	UMap<int, Str>         m_group_per_entity;
};

#endif // REGISTRY_H
