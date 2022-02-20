#include "Movement_System.h"

#include "../Game.h"
#include "../Components/Transform_Component.h"
#include "../Components/Rigid_Body_Component.h"
#include "../Components/Sprite_Component.h"
#include "../Event_Bus/Event_Bus.h"
#include "../Events/Collision_Event.h"



// ---------------------------------------------------
// Internal functions
// ---------------------------------------------------

void on_enemey_hits_obstacle(Entity enemy, Entity obstacle)
{
	if (enemy.has_component<Rigid_Body_Component>() && enemy.has_component<Sprite_Component>()) {
		auto& rigid_body = enemy.component<Rigid_Body_Component>();
		auto& sprite     = enemy.component<Sprite_Component>();

		if (rigid_body.velocity.x != 0) {
			rigid_body.velocity.x *= -1;
			sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}
		if (rigid_body.velocity.y != 0) {
			rigid_body.velocity.y *= -1;
			sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
		}
	}
}




// ---------------------------------------------------
// Class implementation
// ---------------------------------------------------

Movement_System::Movement_System()
{
	require_component<Transform_Component>();
	require_component<Rigid_Body_Component>();
}

void Movement_System::update(double delta_time)
{
	for (auto e : system_entities()) {
		auto& transform = e.component<Transform_Component>();
		const auto rigid_body = e.component<Rigid_Body_Component>();

		transform.position.x += rigid_body.velocity.x * delta_time;
		transform.position.y += rigid_body.velocity.y * delta_time;

		if (e.has_tag("player")) {
			auto padding_left = 10;
			auto padding_top = 10;
			auto padding_right = 50;
			auto padding_bottom = 50;

			transform.position.x = transform.position.x < padding_left ? padding_left : transform.position.x;
			transform.position.x = transform.position.x > Game::map_width - padding_right ? Game::map_width - padding_right : transform.position.x;
			transform.position.y = transform.position.y < padding_top ? padding_top : transform.position.y;
			transform.position.y = transform.position.y > Game::map_height - padding_bottom ? Game::map_height - padding_bottom : transform.position.y;
		}

		const auto is_entity_outside_world =
			transform.position.x < 0               ||
			transform.position.x > Game::map_width ||
			transform.position.y < 0               ||
			transform.position.y > Game::map_height;

		if (is_entity_outside_world && !e.has_tag("player")) {
			e.kill();
		}
	}
}

void Movement_System::subscribe_to_events(Unique<Event_Bus>& event_bus)
{
	event_bus->subscribe_to_event<Collision_Event>(this, &Movement_System::on_collision);
}

void Movement_System::on_collision(Collision_Event& e)
{
	auto a = e.a;
	auto b = e.b;

	if (a.belongs_to_group("enemies") && b.belongs_to_group("obstacles")) {
		on_enemey_hits_obstacle(a, b);
	}

	if (b.belongs_to_group("obstacles") && a.belongs_to_group("enemies")) {
		on_enemey_hits_obstacle(b, a);
	}
}