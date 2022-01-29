#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

#include "../Asset_Id.h"

struct Sprite_Component {
	Asset_Id asset_id;
	int width;
	int height;
	int z_index; // TODO use an enum for layer maybe?
	bool is_fixed;
	SDL_Rect src_rect;

	Sprite_Component(Asset_Id asset_id = Asset_Id::none(), int w = 0, int h = 0, int z = 0, bool is_fixed = false, int src_rect_x = 0, int src_rect_y = 0)
		: asset_id{ asset_id }, width{ w }, height{ h }, z_index{z}, is_fixed{is_fixed}
	{
		src_rect = {
			src_rect_x,
			src_rect_y,
			width,
			height
		};
	}
};