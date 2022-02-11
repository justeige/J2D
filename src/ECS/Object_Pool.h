#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <JUL/Container.h>

class Object_Pool_Base {
public:
	virtual ~Object_Pool_Base() {}
	virtual void remove_entity_from_pool(int entity_id) = 0;
};

template <class T>
class Object_Pool : public Object_Pool_Base {
public:
	Object_Pool(int capacity = 100)
	{
		resize(capacity);
	}
	virtual ~Object_Pool() = default;

	bool is_empty() const 
	{ 
		return m_size == 0; 
	}

	int size() const 
	{ 
		return m_size; 
	}

	void resize(int n) 
	{ 
		m_data.resize(n);
	}

	void clear() 
	{ 
		m_data.clear();
		m_entity_id_to_index.clear();
		m_index_to_entity_id.clear();
		m_size = 0;
	}

	void add(T object)
	{
		m_data.push_back(object);
	}

	void set(int entity_id, const T& object)
	{
		if (m_entity_id_to_index.find(entity_id) != m_entity_id_to_index.end()) {
			// element already exist, replace:
			const auto index = m_entity_id_to_index[entity_id];
			m_data[index] = object;
		}
		else {
			// new element:
			const auto index = m_size;
			m_entity_id_to_index.emplace(entity_id, index);
			m_index_to_entity_id.emplace(index, entity_id);
			if (index >= m_data.capacity()) {
				m_data.resize(m_size * 2);
			}
			m_data[index] = object;
			m_size++;
		}
	}

	void remove(int entity_id)
	{
		// move the last element to the deleted position to keep the array packed:
		const auto index_of_removed = m_entity_id_to_index[entity_id];
		const auto index_of_last = m_size - 1;
		m_data[index_of_removed] = m_data[index_of_last];

		// update index-entity maps
		const auto entity_id_of_last = m_index_to_entity_id[index_of_last];
		m_entity_id_to_index[entity_id_of_last] = index_of_removed;
		m_index_to_entity_id[index_of_removed] = entity_id_of_last;

		// remove from the maps
		m_entity_id_to_index.erase(entity_id);
		m_index_to_entity_id.erase(index_of_last);

		m_size--;
	}

	T& get(int entity_id)
	{
		const auto index = m_entity_id_to_index[entity_id];
		return static_cast<T&>(m_data[index]);
	}

	T& operator [](unsigned int index)
	{
		return m_data[index];
	}

	void remove_entity_from_pool(int entity_id) override
	{
		if (m_entity_id_to_index.find(entity_id) != m_entity_id_to_index.end()) {
			remove(entity_id);
		}
	}

private:
	// TODO add name in debug build
	int m_size = 0;
	Vec<T> m_data;

	// helper maps to keep tracks of entity ids per index,
	// so the vector is always packed
	UMap<int, int> m_entity_id_to_index;
	UMap<int, int> m_index_to_entity_id;
};

#endif // !OBJECT_POOL_H

