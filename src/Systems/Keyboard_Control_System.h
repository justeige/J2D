#pragma once

// TODO add guards
// TODO split into c++ file

#include "../ECS/ECS.h"
#include "../Event_Bus/Event_Bus.h"
#include "../Events/Key_Pressed_Event.h"

#include "../Components/Keyboard_Controlled_Component.h"
#include "../Components/Sprite_Component.h"
#include "../Components/Rigid_Body_Component.h"

class Keyboard_Control_System : public System {
public:

	Keyboard_Control_System()
	{
		require_component<Keyboard_Controlled_Component>();
		require_component<Sprite_Component>();
		require_component<Rigid_Body_Component>();
	}

	void subscribe_to_events(Unique<Event_Bus>& event_bus)
	{
		event_bus->subscribe_to_event<Key_Pressed_Event>(this, &Keyboard_Control_System::on_key_pressed);
	}

	void on_key_pressed(Key_Pressed_Event& key_event)
	{
		for (auto entity : system_entities()) {
			const auto keyboard_control = entity.component<Keyboard_Controlled_Component>();
			auto& sprite     = entity.component<Sprite_Component>();
			auto& rigid_body = entity.component<Rigid_Body_Component>();

			switch (key_event.key_code) {
			case SDLK_UP:
				rigid_body.velocity = keyboard_control.up_velocity;
				sprite.src_rect.y = sprite.height * 0;
				break;

			case SDLK_RIGHT:
				rigid_body.velocity = keyboard_control.right_velocity;
				sprite.src_rect.y = sprite.height * 1;
				break;

			case SDLK_DOWN:
				rigid_body.velocity = keyboard_control.down_velocity;
				sprite.src_rect.y = sprite.height * 2;
				break;

			case SDLK_LEFT:
				rigid_body.velocity = keyboard_control.left_velocity;
				sprite.src_rect.y = sprite.height * 3;
				break;

			default:
				break;
			}
		}
	}

	void update()
	{

	}
};