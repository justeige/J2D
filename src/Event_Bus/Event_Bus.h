#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include "../J2D_Defs.h"
#include "Event.h"

#include <list>



class Event_Callback_Base {
public:
	virtual ~Event_Callback_Base() = default;

	void execute(Event& e) { call(e); }

private:
	virtual void call(Event& e) = 0;
};

template <class TOwner, class TEvent>
class Event_Callback : public Event_Callback_Base {

	typedef void (TOwner::* Callback_Function)(TEvent&);

public:
	Event_Callback(TOwner* owner_inst, Callback_Function callback_func) 
		: m_owner_instance{owner_inst}, m_callback_func{callback_func}
	{
	}

private:

	TOwner*           m_owner_instance;
	Callback_Function m_callback_func;

	virtual void call(Event& e) override 
	{
		std::invoke(m_callback_func, m_owner_instance, static_cast<TEvent&>(e));
	}
};

using Handler_List = std::list<Unique<Event_Callback_Base>>;

class Event_Bus {
public:
	Event_Bus() = default;
	~Event_Bus() = default;

	void reset() { m_subscribers.clear(); }

	template <class TEvent, class TOwner>
	void subscribe_to_event(TOwner* owner_instance, void (TOwner::* callback_function)(TEvent&))
	{
		if (!m_subscribers[typeid(TEvent)].get()) {
			m_subscribers[typeid(TEvent)] = std::make_unique<Handler_List>();
		}
		auto subscriber = std::make_unique<Event_Callback<TOwner, TEvent>>(owner_instance, callback_function);
		m_subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
	}

	template <class TEvent, class ...TArgs>
	void emit(TArgs&& ...args)
	{
		auto handlers = m_subscribers[typeid(TEvent)].get();
		if (handlers) {
			for (auto it = handlers->begin(); it != handlers->end(); ++it) {
				auto handler = it->get();
				TEvent e {std::forward<TArgs>(args)...};
				handler->execute(e);
			}
		}
	}


private:
	Map<std::type_index, Unique<Handler_List>> m_subscribers;
};

#endif // !EVENT_BUS_H



