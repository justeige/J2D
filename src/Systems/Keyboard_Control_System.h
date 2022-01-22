#pragma once

// TODO add guards
// TODO split into c++ file

#include "../ECS/ECS.h"
#include "../Event_Bus/Event_Bus.h"
#include "../Events/Key_Pressed_Event.h"

#include "../Components/Rigid_Body_Component.h"
#include "../Components/Sprite_Component.h"

class Keyboard_Control_System : public System {
public:

	Keyboard_Control_System()
	{
		require_component<Sprite_Component>();
		require_component<Rigid_Body_Component>();
	}

	void subscribe_to_events(Unique<Event_Bus>& event_bus)
	{
		event_bus->subscribe_to_event<Key_Pressed_Event>(this, &Keyboard_Control_System::on_key_pressed);
	}

	void on_key_pressed(Key_Pressed_Event& key_event)
	{
		//const auto key_code = std::to_string(key_event.key_code);
		//const auto key_symbol = std::string{ 1, key_event.key_code };
	}

	void update()
	{

	}
};