#include "Damage_System.h"

#include "../Components/Box_Collider_Component.h"
#include "../Components/Projectile_Component.h"
#include "../Components/Health_Component.h"
#include "../Event_Bus/Event_Bus.h"
#include "../Events/Collision_Event.h"
#include "../Logger.h"



// ---------------------------------------------------
// Internal functions
// ---------------------------------------------------

void on_projectile_hits_player(Entity projectile, Entity player)
{
	const auto projectile_component = projectile.component<Projectile_Component>();

	if (!projectile_component.is_friendly) {
		auto& health = player.component<Health_Component>();

		health.health_percentage -= projectile_component.hit_percent_damage;

		if (health.health_percentage <= 0) {
			player.kill();
		}

		projectile.kill();
	}
}

void on_projectile_hits_enemy(Entity projectile, Entity enemy)
{
	const auto projectile_component = projectile.component<Projectile_Component>();
	
	if (projectile_component.is_friendly) {
		auto& health = enemy.component<Health_Component>();
	
		health.health_percentage -= projectile_component.hit_percent_damage;
	
		if (health.health_percentage <= 0) {
			enemy.kill();
		}
	
		projectile.kill();
	}
}



// ---------------------------------------------------
// Class implementation
// ---------------------------------------------------

Damage_System::Damage_System()
{
	require_component<Box_Collider_Component>();
}

void Damage_System::subscribe_to_events(Unique<Event_Bus>& event_bus)
{
	event_bus->subscribe_to_event<Collision_Event>(this, &Damage_System::on_collision);
}

void Damage_System::on_collision(Collision_Event& e)
{
	auto a = e.a;
	auto b = e.b;

	if (a.belongs_to_group("projectiles") && b.has_tag("player")) {
		on_projectile_hits_player(a, b);
	}

	if (b.belongs_to_group("projectiles") && a.has_tag("player")) {
		on_projectile_hits_player(b, a);
	}

	if (a.belongs_to_group("projectiles") && b.belongs_to_group("enemies")) {
		on_projectile_hits_enemy(a, b);
	}

	if (b.belongs_to_group("projectiles") && a.belongs_to_group("enemies")) {
		on_projectile_hits_enemy(b, a);
	}
}
