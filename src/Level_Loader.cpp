#include "Level_Loader.h"

#include "Game.h"

#include <JUL/Types.h>
#include <JUL/Pointer.h>
#include <JUL/Macros.h>
using namespace jul;
using namespace jul::types;

#include "J2D_Defs.h"
#include "Logger.h"
#include "ECS/Registry.h"
#include "Asset_Store.h"
#include "Components/Components.h"
#include "Systems/Systems.h"
#include "Event_Bus/Event_Bus.h"
#include <iso646.h>
#include <fstream>

#include <sol/sol.hpp>

// ---------------------------------------
// Game internal functions - Declaration
// ---------------------------------------

void create_player(Unique<Registry>& reg);
void create_tank(Unique<Registry>& reg);
void create_truck(Unique<Registry>& reg);
void create_radar(Unique<Registry>& reg);


Level_Loader::Level_Loader()
{
}

Level_Loader::~Level_Loader()
{
}

void Level_Loader::load(Unique<Registry>& registry, Unique<Asset_Store>& asset_store, SDL_Renderer* renderer, int level)
{
	sol::state lua;
	lua.open_libraries(sol::lib::base);
	lua.script_file("./assets/scripts/level1.lua");

	asset_store->add_texture(renderer, AID_Tank,    "./assets/images/tank-panther-right.png");
	asset_store->add_texture(renderer, AID_Truck,   "./assets/images/truck-ford-right.png");
	asset_store->add_texture(renderer, AID_Chopper, "./assets/images/chopper-spritesheet.png");
	asset_store->add_texture(renderer, AID_Radar,   "./assets/images/radar.png");
	asset_store->add_texture(renderer, AID_Bullet,  "./assets/images/bullet.png");
	asset_store->add_texture(renderer, AID_Tree,    "./assets/images/tree.png");

	asset_store->add_texture(renderer, AID_Jungle,  "./assets/tilemaps/jungle.png");

	asset_store->add_font(AID_Charriot_Font, "./assets/fonts/charriot.ttf", 14);
	asset_store->add_font(AID_Pico8_5_Font,  "./assets/fonts/arial.ttf",    5);
	asset_store->add_font(AID_Pico8_10_Font, "./assets/fonts/arial.ttf",    10);

	create_player(registry);
	create_radar(registry);
	create_tank(registry);
	create_truck(registry);

	const auto tile_size = 32;
	const auto tile_scale = 2.0;
	const auto map_num_cols = 25;
	const auto map_num_rows = 20;
	std::fstream map_stream;
	map_stream.open("./assets/tilemaps/jungle.map");

	repeat(y, map_num_rows) {
		repeat(x, map_num_cols) {
			char ch;
			map_stream.get(ch);
			const auto src_rect_y = std::atoi(&ch) * tile_size;

			map_stream.get(ch);
			const auto src_rect_x = std::atoi(&ch) * tile_size;
			map_stream.ignore();

			auto tile = registry->create_entity();
			tile.group("tiles");
			const auto tile_x = x * tile_scale * tile_size;
			const auto tile_y = y * tile_scale * tile_size;
			tile.add_component<Transform_Component>(Vec2(tile_x, tile_y), Vec2(tile_scale, tile_scale), 0.0);
			tile.add_component<Sprite_Component>(AID_Tile_Map, tile_size, tile_size, 0, false, src_rect_x, src_rect_y);
		}
	}
	map_stream.close();

	Game::map_width = map_num_cols * tile_size * tile_scale;
	Game::map_height = map_num_rows * tile_size * tile_scale;
}

// ----------------------------------------------
// Game internal functions - Implementation
// ----------------------------------------------
void create_player(Unique<Registry>& reg)
{
	auto chopper_vel = 50;
	auto chopper = reg->create_entity();
	chopper.tag("player");
	chopper.add_component<Transform_Component>(Vec2(100, 300), Vec2(1.0, 1.0), 1.0);
	chopper.add_component<Rigid_Body_Component>(Vec2(0, 0));
	chopper.add_component<Sprite_Component>(AID_Chopper, 32, 32, 1);
	chopper.add_component<Animation_Component>(2, 15, true);
	chopper.add_component<Box_Collider_Component>(32, 32);
	chopper.add_component<Camera_Follow_Component>();
	chopper.add_component<Health_Component>(100);
	chopper.add_component<Projectile_Emitter_Component>(Vec2{ 150.0, 150.0 }, 0, 10000, 10, true);
	chopper.add_component<Keyboard_Controlled_Component>(
		Vec2{ 0, -1 * chopper_vel },
		Vec2{ chopper_vel, 0 },
		Vec2{ 0, chopper_vel },
		Vec2{ -1 * chopper_vel,0 }
	);
}

void create_tank(Unique<Registry>& reg)
{
	auto tank = reg->create_entity();
	tank.group("enemies");
	tank.add_component<Transform_Component>(Vec2(500, 495));
	tank.add_component<Rigid_Body_Component>(Vec2(20, 0));
	tank.add_component<Sprite_Component>(AID_Tank, 32, 32, 1);
	tank.add_component<Box_Collider_Component>(32, 32);
	tank.add_component<Projectile_Emitter_Component>(Vec2{ 100.0, 0 }, 5000, 3000, 10, false);
	tank.add_component<Health_Component>(100);
}

void create_truck(Unique<Registry>& reg)
{
	auto truck = reg->create_entity();
	truck.group("enemies");
	truck.add_component<Transform_Component>(Vec2(180, 30));
	truck.add_component<Rigid_Body_Component>(Vec2(0, 20));
	truck.add_component<Sprite_Component>(AID_Truck, 32, 32, 1);
	truck.add_component<Box_Collider_Component>(32, 32);
	truck.add_component<Projectile_Emitter_Component>(Vec2{ 0, 100 }, 2000, 5000, 10, false);
	truck.add_component<Health_Component>(100);
}

void create_radar(Unique<Registry>& reg)
{
	auto radar = reg->create_entity();
	radar.add_component<Transform_Component>(Vec2(Game::window_width - 75, 20), Vec2(1.0, 1.0), 1.0);
	radar.add_component<Rigid_Body_Component>(Vec2(0, 0));
	radar.add_component<Sprite_Component>(AID_Radar, 64, 64, 2, true);
	radar.add_component<Animation_Component>(8, 5, true);
}