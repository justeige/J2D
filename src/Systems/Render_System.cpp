#include "Render_System.h"

#include "../Asset_Store.h"
#include "../Components/Components.h"

#include <algorithm>

#include <SDL.h>

Render_System::Render_System()
{
	require_component<Sprite_Component>();
	require_component<Transform_Component>();
}

void Render_System::update(SDL_Renderer* renderer, std::unique_ptr<Asset_Store>& asset_store, SDL_Rect& camera)
{
	// TODO use changed flag from system and store renderable entites as parameters

	struct Renderable_Entity {
		Transform_Component transform_comp;
		Sprite_Component sprite_comp;
	};
	std::vector<Renderable_Entity> renderable_entities;
	for (auto entity : system_entities()) {
		Renderable_Entity renderable_entity;
		renderable_entity.sprite_comp    = entity.component<Sprite_Component>();
		renderable_entity.transform_comp = entity.component<Transform_Component>();
		renderable_entities.emplace_back(renderable_entity);
	}

	std::sort(renderable_entities.begin(), renderable_entities.end(), [](const auto a, const auto b) {
		return a.sprite_comp.z_index < b.sprite_comp.z_index;
	});

	for (auto entity : renderable_entities) {
		const auto transform = entity.transform_comp;
		const auto sprite    = entity.sprite_comp;
		const auto src_rect  = sprite.src_rect;
		const auto dst_rect  = create_rect_from(sprite, transform, camera);

		SDL_RenderCopyEx(
			renderer,
			asset_store->texture(sprite.asset_id),
			&src_rect,
			&dst_rect,
			transform.rotation,
			nullptr, // == center
			SDL_FLIP_NONE
		);
	}
}