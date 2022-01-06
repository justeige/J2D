#ifndef COMPONENT_H
#define COMPONENT_H

class Component_Base {
protected:
	static int next_id;
};

template <class T>
class Component : Component_Base {
public:
	static int id() {
		static auto id = next_id++;
		return id;
	}
};

#endif // !COMPONENT_H

