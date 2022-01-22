#include "Game.h"

#include <JUL/Types.h>
#include <JUL/Pointer.h>
#include <JUL/Macros.h>
using namespace jul;
using namespace jul::types;

#include <SDL.h>
#include <SDL_image.h>
#include "J2D_Defs.h"
#include "Logger.h"
#include "ECS/ECS.h"
#include "Asset_Store.h"
#include "Components/Components.h"
#include "Systems/Systems.h"
#include "Event_Bus/Event_Bus.h"
#include <iso646.h>
#include <fstream>

// ---------------------------------------
// Game constants
// ---------------------------------------

constexpr auto FPS = 60;
constexpr auto MILLISECONDS_PER_FRAME = 1000 / FPS;


// ---------------------------------------
// Game data
// ---------------------------------------

struct Game::Data {
	bool isRunning         = false;
	SDL_Window*   window   = nullptr;
	SDL_Renderer* renderer = nullptr;

	u32 window_width       = 0;
	u32 window_height      = 0;
	u32 ms_previous_frame  = 0;

	Unique<Registry>    registry    = std::make_unique<Registry>();
	Unique<Asset_Store> asset_store = std::make_unique<Asset_Store>();
	Unique<Event_Bus>   event_bus   = std::make_unique<Event_Bus>();
};



Game::Game() : m{new Data}
{
}

Game::~Game()
{
}

void Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::err("Error initializing SDL.");
		return;
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	m->window_width  = display_mode.w;
	m->window_height = display_mode.h;

	m->window = SDL_CreateWindow(
		"J2D Engine",           // title
		SDL_WINDOWPOS_CENTERED, // x
		SDL_WINDOWPOS_CENTERED, // y
		m->window_width,        // w
		m->window_height,       // h
		SDL_WINDOW_BORDERLESS   // flags
	);

	if (!m->window) {
		Logger::err("Error creating SDL window.");
		return;
	}

	m->renderer = SDL_CreateRenderer(
		m->window, // window
		-1,        // index (-1 == default)
		0          // flags
	);

	if (!m->renderer) {
		Logger::err("Error creating SDL renderer.");
		return;
	}

	// changes the video-mode to fullscreen
	SDL_SetWindowFullscreen(m->window, SDL_WINDOW_FULLSCREEN);

	m->isRunning = true;
}



void Game::setup()
{
	m->registry->add_system<Movement_System>();
	m->registry->add_system<Render_System>();
	m->registry->add_system<Animation_System>();
	m->registry->add_system<Collision_System>();
	m->registry->add_system<Damage_System>();
	m->registry->add_system<Keyboard_Control_System>();

	m->asset_store->add_texture(m->renderer, AID_Tank, "./assets/images/tank-panther-right.png");
	m->asset_store->add_texture(m->renderer, AID_Truck, "./assets/images/truck-ford-right.png");
	m->asset_store->add_texture(m->renderer, AID_Chopper, "./assets/images/chopper.png");
	m->asset_store->add_texture(m->renderer, AID_Radar, "./assets/images/radar.png");
	m->asset_store->add_texture(m->renderer, AID_Jungle, "./assets/tilemaps/jungle.png");

	auto chopper = m->registry->create_entity();
	chopper.add_component<Transform_Component>(Vec2(100, 300), Vec2(1.0, 1.0), 1.0);
	chopper.add_component<Rigid_Body_Component>(Vec2(0, 0));
	chopper.add_component<Sprite_Component>(AID_Chopper, 32, 32, 1);
	chopper.add_component<Animation_Component>(2, 5, true);

	auto radar = m->registry->create_entity();
	radar.add_component<Transform_Component>(Vec2(m->window_width - 75, 20), Vec2(1.0, 1.0), 1.0);
	radar.add_component<Rigid_Body_Component>(Vec2(0, 0));
	radar.add_component<Sprite_Component>(AID_Radar, 64, 64, 2);
	radar.add_component<Animation_Component>(8, 5, true);


	auto tank = m->registry->create_entity();
	tank.add_component<Transform_Component>(Vec2(10, 30));
	tank.add_component<Rigid_Body_Component>(Vec2(20, 0));
	tank.add_component<Sprite_Component>(AID_Tank, 32, 32, 1);
	tank.add_component<Box_Collider_Component>(32, 32);
	
	auto truck = m->registry->create_entity();
	truck.add_component<Transform_Component>(Vec2(180, 30));
	truck.add_component<Rigid_Body_Component>(Vec2(-20, 0));
	truck.add_component<Sprite_Component>(AID_Truck, 32, 32, 1);
	truck.add_component<Box_Collider_Component>(32, 32);

	load_tilemap("./assets/tilemaps/jungle.map");
}

void Game::run()
{
	setup();

	while (m->isRunning) {
		process_input();
		update();
		render();
	}
}

void Game::process_input()
{
	SDL_Event sdl_event;
	while (SDL_PollEvent(&sdl_event)) {
		switch (sdl_event.type)
		{
		case SDL_QUIT:
			m->isRunning = false;
			break;

		case SDL_KEYDOWN:
			if (sdl_event.key.keysym.sym == SDLK_ESCAPE) {
				m->isRunning = false;
			}

			m->event_bus->emit<Key_Pressed_Event>(sdl_event.key.keysym.sym);
			break;

		default:
			break;
		}
	}
}

void Game::update()
{
	// fps capping: ensure a faster pc doesn't go over 60 fps
	const auto time_to_wait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - m->ms_previous_frame);
	if (time_to_wait > 0 && time_to_wait <= MILLISECONDS_PER_FRAME) {
		SDL_Delay(time_to_wait);
	}

	// delta time is used so all our movements are in line with
	// our selected frame rate
	const auto delta_time = (SDL_GetTicks() - m->ms_previous_frame) / 1000.0;
	m->ms_previous_frame = SDL_GetTicks();

	// reset all events handlers
	m->event_bus->reset();

	// event subscriptions are per frame
	m->registry->system<Damage_System>().subscribe_to_events(m->event_bus);
	m->registry->system<Keyboard_Control_System>().subscribe_to_events(m->event_bus);

	// update systems & registry
	m->registry->update_entities();

	m->registry->system<Movement_System>().update(delta_time);
	m->registry->system<Animation_System>().update();
	m->registry->system<Collision_System>().update(m->event_bus);
}

void Game::render()
{
	SDL_SetRenderDrawColor(m->renderer, 21, 21, 21, 255);
	SDL_RenderClear(m->renderer);

	m->registry->system<Render_System>().update(m->renderer, m->asset_store);

	SDL_RenderPresent(m->renderer);
}

void Game::destroy()
{
	SDL_DestroyRenderer(m->renderer);
	SDL_DestroyWindow(m->window);
	SDL_Quit();
}


void Game::load_tilemap(const char* name)
{
	const auto tile_size    = 32;
	const auto tile_scale   = 2.0;
	const auto map_num_cols = 25;
	const auto map_num_rows = 20;
	std::fstream map_stream;
	map_stream.open(name);

	repeat (y, map_num_rows) {
		repeat (x, map_num_cols) {
			char ch;
			map_stream.get(ch);
			const auto src_rect_y = std::atoi(&ch) * tile_size;

			map_stream.get(ch);
			const auto src_rect_x = std::atoi(&ch) * tile_size;
			map_stream.ignore();

			auto tile = m->registry->create_entity();
			const auto tile_x = x * tile_scale * tile_size;
			const auto tile_y = y * tile_scale * tile_size;
			tile.add_component<Transform_Component>(Vec2(tile_x, tile_y), Vec2(tile_scale, tile_scale), 0.0);
			tile.add_component<Sprite_Component>(AID_Tile_Map, tile_size, tile_size, 0, src_rect_x, src_rect_y);
		}
	}
	map_stream.close();
}