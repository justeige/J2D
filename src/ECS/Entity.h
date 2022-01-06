#ifndef ENTITY_H
#define ENTITY_H

class Registry;

class Entity {
public:
	Entity(int id, Registry* reg) : m_id(id), m_registry(reg) {}
	Entity(const Entity& e) : m_id(e.id()), m_registry(e.registry()) {}

	int id() const { return m_id; }
	Registry* registry() const { return m_registry; }

	Entity& operator =(const Entity& other)
	{
		m_id = other.id();
		return *this;
	}

	bool operator == (const Entity& other) const
	{
		return m_id == other.id();
	}

	bool operator != (const Entity& other) const
	{
		return m_id != other.id();
	}

	bool operator < (const Entity& other) const
	{
		return m_id < other.id();
	}

	bool operator > (const Entity& other) const
	{
		return m_id > other.id();
	}

	template <class T, class ...TArgs>
	void add_component(TArgs&& ...args);

	template <class T>
	T& component() const;

private:
	int m_id = 0;
	Registry* m_registry = nullptr;
};

#endif // ENTITY_H
