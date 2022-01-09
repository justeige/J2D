#include "Registry.h"


Entity Registry::create_entity()
{
	auto entity_id = 0;
	
	if (m_free_ids.empty()) {
		// no free ids, get a new one
		entity_id = m_num_entities++;
		if (entity_id >= m_entity_component_signatures.size()) {
			m_entity_component_signatures.resize(entity_id + 1);
		}
	}
	else {
		// a free id is available, reuse it
		entity_id = m_free_ids.front();
		m_free_ids.pop_front();
	}

	const auto new_entity = Entity(entity_id, this);
	m_entities_to_be_added.insert(new_entity);
	return new_entity;
}

void Registry::kill_entity(Entity e)
{
	m_entities_to_be_removed.insert(e);
}

void Registry::update_entities()
{
	for (auto e : m_entities_to_be_added) {
		add_entity_to_systems(e);
	}
	m_entities_to_be_added.clear();


	for (auto e : m_entities_to_be_removed) {
		const auto entity_id = e.id();
		remove_entity_from_systems(e);
		m_entity_component_signatures[entity_id].reset();
		m_free_ids.push_back(entity_id);
	}
	m_entities_to_be_removed.clear();
}

void Registry::add_entity_to_systems(Entity e)
{
	const auto entity_id = e.id();

	const auto entity_component_signature = m_entity_component_signatures[entity_id];

	for (auto& [_, system] : m_systems) {
		const auto& system_component_signature = system->component_signature();

		if (are_matching(entity_component_signature, system_component_signature)) {
			system->add_entity(e);
		}
	}
}

void Registry::remove_entity_from_systems(Entity e)
{
	for (auto& [_, system] : m_systems) {
		system->remove_entity(e);
	}
}
