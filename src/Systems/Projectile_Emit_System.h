#pragma once

// TODO guards, c++ split


#include "../ECS/ECS.h"
#include "../Components/Transform_Component.h"
#include "../Components/Project_Emitter_Component.h"
#include "../Components/Rigid_Body_Component.h"
#include "../Components/Sprite_Component.h"
#include "../Components/Box_Collider_Component.h"
#include "../Components/Projectile_Component.h"
#include "../Components/Camera_Follow_Component.h"
#include <SDL.h>


class Projectile_Emit_System : public System {
public:
	Projectile_Emit_System()
	{
		require_component<Projectile_Emitter_Component>();
		require_component<Transform_Component>();
	}

	void update(Unique<Registry>& registry)
	{
		for (auto entity : system_entities()) {
			auto& projectile_emitter = entity.component<Projectile_Emitter_Component>();
			const auto transform     = entity.component<Transform_Component>();

			if (projectile_emitter.repeat_frequency == 0) { continue; }

			if (! time_to_emit_new_projectile(projectile_emitter)) { continue; }

			auto projectile_position = transform.position;
			if (entity.has_component<Sprite_Component>()) {
				const auto sprite = entity.component<Sprite_Component>();
				projectile_position.x += (transform.scale.x * sprite.width / 2);
				projectile_position.y += (transform.scale.y * sprite.height / 2);
			}

			auto projectile = registry->create_entity();
			projectile.group("projectiles");
			projectile.add_component<Transform_Component>(projectile_position, Vec2{ 1.0, 1.0 }, 0.0);
			projectile.add_component<Rigid_Body_Component>(projectile_emitter.projectile_velocity);
			projectile.add_component<Sprite_Component>(AID_Bullet, 4, 4, 4);
			projectile.add_component<Box_Collider_Component>(4, 4);
			projectile.add_component<Projectile_Component>(
				projectile_emitter.is_friendly,
				projectile_emitter.hit_percentage_dmg,
				projectile_emitter.projectile_duration
			);

			projectile_emitter.last_emission_time = SDL_GetTicks();
		}
	}

	void subscribe_to_events(Unique<Event_Bus>& event_bus)
	{
		event_bus->subscribe_to_event<Key_Pressed_Event>(this, &Projectile_Emit_System::on_key_pressed);
	}

	void on_key_pressed(Key_Pressed_Event& key_event)
	{
		if (key_event.key_code != SDLK_SPACE) { return; }

		for (auto entity : system_entities()) {
			if (!entity.has_component<Camera_Follow_Component>()) { continue; }

			const auto projectile_emitter = entity.component<Projectile_Emitter_Component>();
			const auto transform  = entity.component<Transform_Component>();
			const auto rigid_body = entity.component<Rigid_Body_Component>();

			auto projectile_pos = transform.position;
			if (entity.has_component<Sprite_Component>()) {
				auto sprite = entity.component<Sprite_Component>();
				projectile_pos.x += (transform.scale.x * sprite.width  / 2);
				projectile_pos.y += (transform.scale.y * sprite.height / 2);
			}

			const auto projectile_velocity = direction_of_projectile(projectile_emitter, rigid_body);

			auto projectile = entity.registry()->create_entity();
			projectile.group("projectiles");
			projectile.add_component<Transform_Component>(projectile_pos, Vec2{1.0, 1.0}, 0.0);
			projectile.add_component<Rigid_Body_Component>(projectile_velocity);
			projectile.add_component<Sprite_Component>(AID_Bullet, 4, 4, 4);
			projectile.add_component<Box_Collider_Component>(4, 4);
			projectile.add_component<Projectile_Component>(
				projectile_emitter.is_friendly, 
				projectile_emitter.hit_percentage_dmg, 
				projectile_emitter.projectile_duration
			);

		}
	}
};
