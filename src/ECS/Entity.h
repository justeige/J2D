#ifndef ENTITY_H
#define ENTITY_H

#include <JUL/Container.h>
using namespace jul;

class Registry;

class Entity {
public:
	Entity(int id, Registry* reg) : m_id(id), m_registry(reg) {}
	Entity(const Entity& e) : m_id(e.id()), m_registry(e.registry()) {}

	int id() const { return m_id; }
	Registry* registry() const { return m_registry; }
	void kill();


	// ------------------------
	// Comparisons
	// ------------------------

	Entity& operator =(const Entity& other);
	bool operator == (const Entity& other) const;
	bool operator != (const Entity& other) const;
	bool operator <  (const Entity& other) const;
	bool operator >  (const Entity& other) const;



	// ------------------------
	// Access to components
	// ------------------------

	template <class T, class ...TArgs>
	void add_component(TArgs&& ...args);

	template <class T>
	T& component() const;

	template <class T>
	bool has_component() const;



	// ------------------------
	// Tagging and grouping
	// ------------------------
	void tag(const Str& tag);
	bool has_tag(const Str& tag) const;
	void group(const Str& group);
	bool belongs_to_group(const Str& group) const;


private:
	int m_id = 0;
	Registry* m_registry = nullptr;
};

#endif // ENTITY_H
