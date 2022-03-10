#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

// TODO

#include <JUL/Types.h>
#include <JUL/Pointer.h>
#include <JUL/Macros.h>
using namespace jul;
using namespace jul::types;

#include "SDL_fwd.h"
class Registry;
class Asset_Store;

class Level_Loader {
public:
	Level_Loader();
	~Level_Loader();

	void load(Unique<Registry>& registry, Unique<Asset_Store>& asset_store, SDL_Renderer* renderer, int level);
};


#endif // !LEVEL_LOADER_H