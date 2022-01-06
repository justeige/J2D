#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "../ECS/ECS.h"
#include "../SDL_fwd.h"

class Asset_Store;

class Render_System : public System {
public:
	Render_System();

	void update(SDL_Renderer* renderer, std::unique_ptr<Asset_Store>& asset_store);
};

#endif // !RENDER_SYSTEM_H