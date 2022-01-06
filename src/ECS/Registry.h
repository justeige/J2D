#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <set>

#include "Signature.h"
#include "System.h"
#include "Object_Pool.h"
#include "Entity.h"

class Registry {
public:

	Entity create_entity();
	void kill_entity(Entity e);
	void update();
	void add_entity_to_systems(Entity e);

	template <class T, class ...TArgs>
	void add_component(Entity e, TArgs&& ...args);

	template <class T>
	void remove_component(Entity e);

	template <class T>
	bool has_component(Entity e);

	template <class T>
	T& component(Entity e) const;


	template <class TSystem, class ...TArgs>
	void add_system(TArgs&& ...args);

	template <class TSystem>
	void remove_system();

	template <class TSystem>
	bool has_system() const;

	template <class TSystem>
	TSystem& system() const;

private:
	int num_entities = 0;

	std::set<Entity> entities_to_be_added;
	std::set<Entity> entities_to_be_removed;
	std::vector<std::shared_ptr<Object_Pool_Base>> component_pools;
	std::vector<Signature> entity_component_signatures;
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
};

#endif // REGISTRY_H
