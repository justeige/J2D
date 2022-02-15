#pragma once
// TODO ..

#include "../J2D_Defs.h"
#include <SDL.h>

struct Text_Label_Component {
	Vec2 position;
	Str text;
	Asset_Id asset_id;
	SDL_Color color;
	bool is_fixed;

	Text_Label_Component(Vec2 pos = Vec2{0}, Str txt = "", Asset_Id id = Asset_Id::none(), const SDL_Color& c = {0, 0, 0}, bool is_fixed = true)
		: position{pos}, text{txt}, asset_id{id}, color{c}, is_fixed{is_fixed}
	{
	}
};
