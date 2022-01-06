#include "Registry.h"


Entity Registry::create_entity()
{
	const auto entity_id = num_entities++;
	if (entity_id >= entity_component_signatures.size()) {
		entity_component_signatures.resize(entity_id + 1);
	}

	const auto new_entity = Entity(entity_id, this);
	entities_to_be_added.insert(new_entity);
	return new_entity;
}

void Registry::kill_entity(Entity e)
{
}

void Registry::update()
{
	for (auto e : entities_to_be_added) {
		add_entity_to_systems(e);
	}

	entities_to_be_added.clear();
}

void Registry::add_entity_to_systems(Entity e)
{
	const auto entity_id = e.id();

	const auto entity_component_signature = entity_component_signatures[entity_id];

	for (auto& [_, system] : systems) {
		const auto& system_component_signature = system->component_signature();

		// TODO make free function "is matching"
		const auto is_matching = (entity_component_signature & system_component_signature) == system_component_signature;

		if (is_matching) {
			system->add_entity(e);
		}
	}
}