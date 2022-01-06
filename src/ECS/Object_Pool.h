#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <vector>

class Object_Pool_Base {
public:
	virtual ~Object_Pool_Base() {}
};

template <class T>
class Object_Pool : public Object_Pool_Base {
public:
	Object_Pool(int initial_size = 100)
	{
		resize(initial_size);
	}
	virtual ~Object_Pool() = default;

	bool is_empty() const { return data.empty(); }

	int size() const { return data.size(); }

	void resize(int n) { data.resize(n); }

	void clear() { data.clear(); }

	void add(T object)
	{
		data.push_back(object);
	}

	void set(int index, const T& object)
	{
		data[index] = object;
	}

	T& get(int index)
	{
		return static_cast<T&>(data[index]);
	}

	T& operator [](unsigned int index)
	{
		return data[index];
	}

private:
	std::vector<T> data;
};

#endif // !OBJECT_POOL_H

