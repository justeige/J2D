#ifndef ENTITY_IMPL_H
#define ENTITY_IMPL_H



template <class T, class ...TArgs>
void Entity::add_component(TArgs&& ...args)
{
	m_registry->add_component<T>(*this, std::forward<TArgs>(args)...);
}

template <class T>
T& Entity::component() const
{
	return m_registry->component<T>(*this);
}


#endif // ENTITY_IMPL_H
