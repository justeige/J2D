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

		remove_entity_tag(e);
		remove_entity_from_group(e);
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

void Registry::tag_entity(Entity e, const Str& tag)
{
	m_entity_per_tag.emplace(tag, e);
	m_tag_per_entity.emplace(e.id(), tag);
}

bool Registry::entity_has_tag(Entity e, const Str& tag) const
{
	if (m_tag_per_entity.find(e.id()) == m_tag_per_entity.end()) {
		return false;
	}

	return m_entity_per_tag.find(tag)->second == e;
}

Entity Registry::entity_by_tag(const Str& tag) const
{
	return m_entity_per_tag.at(tag);
}

void Registry::remove_entity_tag(Entity e)
{
	const auto tagged_entity = m_tag_per_entity.find(e.id());
	if (tagged_entity == m_tag_per_entity.end()) { return; }

	const auto tag = tagged_entity->second;
	m_entity_per_tag.erase(tag);
	m_tag_per_entity.erase(tagged_entity);
}

void Registry::group_entity(Entity e, const Str& group)
{
	m_entities_per_group.emplace(group, Set<Entity>());
	m_entities_per_group[group].emplace(e);
	m_group_per_entity.emplace(e.id(), group);
}

bool Registry::entity_belongs_to_group(Entity e, const Str& group) const
{
	if (m_entities_per_group.find(group) == m_entities_per_group.end()) {
		return false;
	}

	auto group_entities = m_entities_per_group.at(group);
	return group_entities.find(e) != group_entities.end();
}

Vec<Entity> Registry::entities_by_group(const Str& group) const
{
	auto& set_of_entities = m_entities_per_group.at(group);
	return Vec<Entity>(set_of_entities.begin(), set_of_entities.end());
}

void Registry::remove_entity_from_group(Entity e)
{
	auto grouped_entity = m_group_per_entity.find(e.id());
	if (grouped_entity != m_group_per_entity.end()) {
		auto group = m_entities_per_group.find(grouped_entity->second);
		if (group != m_entities_per_group.end()) {
			auto entity_in_group = group->second.find(e);
			if (entity_in_group != group->second.end()) {
				group->second.erase(entity_in_group);
			}
		}
		m_group_per_entity.erase(grouped_entity);
	}
}
