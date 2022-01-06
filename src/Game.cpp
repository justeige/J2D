#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include "J2D_Defs.h"
#include "Logger.h"
#include "ECS/ECS.h"
#include "Asset_Store.h"
#include "Components/Components.h"
#include "Systems/Systems.h"
#include <iso646.h>
#include <fstream>

// ---------------------------------------
// Game constants
// ---------------------------------------

constexpr auto FPS = 60;
constexpr auto MILLISECONDS_PER_FRAME = 1000 / FPS;


struct Game::Data {
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int window_width = 0;
	int window_height = 0;
	long ms_previous_frame = 0;
	std::unique_ptr<Registry> registry = std::make_unique<Registry>();
	std::unique_ptr<Asset_Store> asset_store = std::make_unique<Asset_Store>();
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
	m->window_width = display_mode.w;
	m->window_height = display_mode.h;

	m->window = SDL_CreateWindow(
		"J2D Engine", // title
		SDL_WINDOWPOS_CENTERED, // x
		SDL_WINDOWPOS_CENTERED, // y
		m->window_width,  // w
		m->window_height, // h
		SDL_WINDOW_BORDERLESS // flags
	);

	if (!m->window) {
		Logger::err("Error creating SDL window.");
		return;
	}

	m->renderer = SDL_CreateRenderer(
		m->window, // window
		-1,     // index (-1 == default)
		0       // flags
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

	m->asset_store->add_texture(m->renderer, AID_Tank, "./assets/images/tank-panther-right.png");
	m->asset_store->add_texture(m->renderer, AID_Truck, "./assets/images/truck-ford-right.png");
	m->asset_store->add_texture(m->renderer, AID_Chopper, "./assets/images/chopper.png");
	m->asset_store->add_texture(m->renderer, AID_Radar, "./assets/images/radar.png");
	m->asset_store->add_texture(m->renderer, AID_Jungle, "./assets/tilemaps/jungle.png");

	auto chopper = m->registry->create_entity();
	chopper.add_component<Transform_Component>(Vec2(10, 30), Vec2(1.0, 1.0), 1.0);
	chopper.add_component<Rigid_Body_Component>(Vec2(0, 0));
	chopper.add_component<Sprite_Component>(AID_Chopper, 32, 32, 1);
	chopper.add_component<Animation_Component>(2, 5, true);

	auto radar = m->registry->create_entity();
	radar.add_component<Transform_Component>(Vec2(m->window_width - 75, 20), Vec2(1.0, 1.0), 1.0);
	radar.add_component<Rigid_Body_Component>(Vec2(0, 0));
	radar.add_component<Sprite_Component>(AID_Radar, 64, 64, 2);
	radar.add_component<Animation_Component>(8, 5, true);

	//auto tank = m_registry->create_entity();
	//tank.add_component<Transform_Component>(Vec2(10, 30), Vec2(1.0, 1.0), 1.0);
	//tank.add_component<Rigid_Body_Component>(Vec2(50, 10));
	//tank.add_component<Sprite_Component>(AID_Tank, 32, 32, 1);
	//
	//
	//auto truck = m_registry->create_entity();
	//truck.add_component<Transform_Component>(Vec2(100, 500), Vec2(1.0, 1.0), 1.0);
	//truck.add_component<Rigid_Body_Component>(Vec2(500, 0));
	//truck.add_component<Sprite_Component>(AID_Truck, 32, 32, 1);

	// load the tilemap
	const auto tile_size = 32;
	const auto tile_scale = 2.0;
	const auto map_num_cols = 25;
	const auto map_num_rows = 20;
	std::fstream map_stream;
	map_stream.open("./assets/tilemaps/jungle.map");

	for (size_t y = 0; y < map_num_rows; y++) {
		for (size_t x = 0; x < map_num_cols; x++) {
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
			break;

		default:
			break;
		}
	}
}

void Game::update()
{
	// fps capping
	const auto time_to_wait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - m->ms_previous_frame);
	if (time_to_wait > 0 && time_to_wait <= MILLISECONDS_PER_FRAME) {
		SDL_Delay(time_to_wait);
	}

	const auto delta_time = (SDL_GetTicks() - m->ms_previous_frame) / 1000.0;

	m->ms_previous_frame = SDL_GetTicks();

	m->registry->system<Movement_System>().update(delta_time);
	m->registry->system<Animation_System>().update();

	m->registry->update();
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