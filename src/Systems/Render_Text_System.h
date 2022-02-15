#pragma once

// TODO

#include "../ECS/System.h"

#include "../J2D_Defs.h"
#include "../Asset_Store.h"
#include "../Components/Text_Label_Component.h"
#include <SDL.h>
#include <SDL_ttf.h>

class Render_Text_System : public System {
public:
	Render_Text_System()
	{
		require_component<Text_Label_Component>();
	}

	void update(SDL_Renderer* renderer, Unique<Asset_Store>& asset_store, const SDL_Rect& camera)
	{
		for (auto e : system_entities()) {
			const auto text_label = e.component<Text_Label_Component>();

			auto surface = TTF_RenderText_Blended(
				asset_store->font(text_label.asset_id),
				text_label.text.c_str(),
				text_label.color
			);

			auto texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			auto label_width  = 0;
			auto label_height = 0;

			SDL_QueryTexture(texture, nullptr, nullptr, &label_width, &label_height);

			SDL_Rect dst_rect = {
				static_cast<int>(text_label.position.x - (text_label.is_fixed ? 0 : camera.x)),
				static_cast<int>(text_label.position.y - (text_label.is_fixed ? 0 : camera.y)),
				label_width,
				label_height
			};

			SDL_RenderCopy(renderer, texture, nullptr, &dst_rect);
			SDL_DestroyTexture(texture);
		}
	}
};
