#ifndef SYSTEM_IMPL_H
#define SYSTEM_IMPL_H

#include "Component.h"

template <class TComponent>
void System::require_component()
{
	const auto component_id = Component<TComponent>::id();
	m_component_signature.set(component_id);
}

#endif // SYSTEM_IMPL_H
