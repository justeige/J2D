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
#include "Level_Loader.h"
#include "Components/Components.h"
#include "Systems/Systems.h"
#include "Event_Bus/Event_Bus.h"
#include <iso646.h>
#include <fstream>

#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_sdlrenderer.h>

// ---------------------------------------
// Game statics
// ---------------------------------------
// TODO move into singleton "Sizing"
u32 Game::window_width  = 0;
u32 Game::window_height = 0;
u32 Game::map_width     = 0;
u32 Game::map_height    = 0;


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
	SDL_Rect      camera = {};

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

	if (TTF_Init() != 0) {
		Logger::err("Error initializing TTF.");
		return;
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	Game::window_width  = display_mode.w;
	Game::window_height = display_mode.h;

	// for debugging // TODO remove
	Game::window_width  = 1024;
	Game::window_height = 800;

	m->window = SDL_CreateWindow(
		"J2D Engine",           // title
		SDL_WINDOWPOS_CENTERED, // x
		SDL_WINDOWPOS_CENTERED, // y
		Game::window_width,     // w
		Game::window_height,    // h
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

	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(m->window, m->renderer);
	ImGui_ImplSDLRenderer_Init(m->renderer);
	ImGuiSDL::Initialize(m->renderer, Game::window_width, Game::window_height);


	// changes the video-mode to fullscreen
	SDL_SetWindowFullscreen(m->window, SDL_WINDOW_BORDERLESS);

	// set the camera
	m->camera.x = 0;
	m->camera.y = 0;
	m->camera.w = Game::window_width;
	m->camera.h = Game::window_height;

	m->isRunning = true;
}



void Game::setup()
{
	load_systems();


	Level_Loader loader;
	loader.load(m->registry, m->asset_store, m->renderer, 1);


	auto treeA = m->registry->create_entity();
	treeA.group("obstacles");
	treeA.add_component<Transform_Component>(Vec2(600, 495));
	treeA.add_component<Sprite_Component>(AID_Tree, 16, 32, 2);
	treeA.add_component<Box_Collider_Component>(16, 32);

	auto treeB = m->registry->create_entity();
	treeB.group("obstacles");
	treeB.add_component<Transform_Component>(Vec2(400, 495));
	treeB.add_component<Sprite_Component>(AID_Tree, 16, 32, 2);
	treeB.add_component<Box_Collider_Component>(16, 32);

	auto label = m->registry->create_entity();
	SDL_Color white = { 255, 255, 255 };
	label.add_component<Text_Label_Component>(Vec2{100, 100}, "this is my text", AID_Charriot_Font, white, true);

}

void Game::load_assets()
{
	// TODO delete
}

void Game::load_systems()
{
	m->registry->add_system<Movement_System>();
	m->registry->add_system<Render_System>();
	m->registry->add_system<Animation_System>();
	m->registry->add_system<Collision_System>();
	m->registry->add_system<Damage_System>();
	m->registry->add_system<Keyboard_Control_System>();
	m->registry->add_system<Camera_Movement_System>();
	m->registry->add_system<Projectile_Emit_System>();
	m->registry->add_system<Projectile_Lifecycle_System>();
	m->registry->add_system<Render_Text_System>();
	m->registry->add_system<Render_Healthbar_System>();
	m->registry->add_system<Render_GUI_System>();
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
		// ImGui SDL input
		ImGui_ImplSDL2_ProcessEvent(&sdl_event);
		auto& io = ImGui::GetIO();
		auto mouse_x = 0, mouse_y = 0;
		const auto buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

		io.MousePos = ImVec2(mouse_x, mouse_y);
		io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

		// handle core SDL events
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
	m->registry->system<Movement_System>().subscribe_to_events(m->event_bus);
	m->registry->system<Damage_System>().subscribe_to_events(m->event_bus);
	m->registry->system<Keyboard_Control_System>().subscribe_to_events(m->event_bus);
	m->registry->system<Projectile_Emit_System>().subscribe_to_events(m->event_bus);

	// update systems & registry
	m->registry->update_entities();

	m->registry->system<Movement_System>().update(delta_time);
	m->registry->system<Animation_System>().update();
	m->registry->system<Collision_System>().update(m->event_bus);
	m->registry->system<Camera_Movement_System>().update(m->camera);
	m->registry->system<Projectile_Emit_System>().update(m->registry);
	m->registry->system<Projectile_Lifecycle_System>().update();
}

void Game::render()
{
	SDL_SetRenderDrawColor(m->renderer, 21, 21, 21, 255);
	SDL_RenderClear(m->renderer);

	m->registry->system<Render_System>().update(m->renderer, m->asset_store, m->camera);
	m->registry->system<Render_Text_System>().update(m->renderer, m->asset_store, m->camera);
	m->registry->system<Render_Healthbar_System>().update(m->renderer, m->asset_store, m->camera);

	// if debug
	m->registry->system<Render_GUI_System>().update(m->registry);
	// end

	SDL_RenderPresent(m->renderer);
}

void Game::destroy()
{
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();
	SDL_DestroyRenderer(m->renderer);
	SDL_DestroyWindow(m->window);
	SDL_Quit();
}
