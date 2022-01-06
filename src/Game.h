#pragma once

#include <memory>

#include "SDL_fwd.h"

class Registry;
class Asset_Store;



class Game {
public:
	Game();
	~Game();

	void init();
	void run();
	void destroy();

private:
	void process_input();
	void update();
	void render();
	void setup();

	struct Data;
	std::unique_ptr<Data> m;
};

