#pragma once
// TODO

#include "../ECS/System.h"

#include "../J2D_Defs.h"
#include "../Components/Transform_Component.h"
#include "../Components/Sprite_Component.h"
#include "../Components/Health_Component.h"
#include <SDL.h>
#include <SDL_ttf.h>

class Render_Healthbar_System : public System {
public:
	Render_Healthbar_System()
	{
		require_component<Transform_Component>();
		require_component<Sprite_Component>();
		require_component<Health_Component>();
	}

	void update(SDL_Renderer* renderer, Unique<Asset_Store>& asset_store, const SDL_Rect& camera)
	{
		for (auto e : system_entities()) {
			const auto transform = e.component<Transform_Component>();
			const auto sprite = e.component<Sprite_Component>();
			const auto health = e.component<Health_Component>();

			SDL_Color health_bar_color = { 255, 255, 255 };

			if (health.health_percentage >= 0 && health.health_percentage < 40) {
				health_bar_color = { 255, 0, 0 }; // red
			}
			else if (health.health_percentage >= 40 && health.health_percentage < 80) {
				health_bar_color = { 255, 255, 0 }; // yellow
			}
			else if (health.health_percentage >= 80 && health.health_percentage <= 100) {
				health_bar_color = { 0, 255, 0 }; // yellow
			}

			// set pos to middle-bottom of the entity sprite
			auto health_bar_width = 15;
			auto health_bar_height = 3;

			auto health_bar_pos_x = (transform.position.x + (sprite.width * transform.scale.x)) - camera.x;
			auto health_bar_pos_y = (transform.position.y) - camera.y;

			SDL_Rect health_bar_rectangle = {
				static_cast<int>(health_bar_pos_x),
				static_cast<int>(health_bar_pos_y),
				static_cast<int>(health_bar_width * (health.health_percentage / 100.0)),
				static_cast<int>(health_bar_height)
			};

			SDL_SetRenderDrawColor(renderer, health_bar_color.r, health_bar_color.g, health_bar_color.b, 255);
			SDL_RenderFillRect(renderer, &health_bar_rectangle);

			// render health percentage text label
			const auto health_text = std::to_string(health.health_percentage);
			auto surface = TTF_RenderText_Blended(
				asset_store->font(AID_Pico8_5_Font), 
				health_text.c_str(), 
				health_bar_color
			);
			auto texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			auto label_width  = 0;
			auto label_height = 0;

			SDL_QueryTexture(texture, nullptr, nullptr, &label_width, &label_height);
			SDL_Rect health_bar_text_rect = {
				static_cast<int>(health_bar_pos_x),
				static_cast<int>(health_bar_pos_y) + 5,
				label_width,
				label_height
			};

			SDL_RenderCopy(renderer, texture, nullptr, &health_bar_text_rect);
			SDL_DestroyTexture(texture);
		}
	}

private:
};
