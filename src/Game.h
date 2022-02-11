#ifndef GAME_H
#define GAME_H

#include <memory>
#include <stdint.h>

class Game {
public:
	Game();
	~Game();

	void init();
	void run();
	void destroy();

	static uint32_t window_width;
	static uint32_t window_height;
	static uint32_t map_width;
	static uint32_t map_height;

private:
	void process_input();
	void update();
	void render();
	void setup();
	void load_tilemap(const char* name);
	void load_assets();
	void load_systems();

	struct Data;
	std::unique_ptr<Data> m;
};

#endif // !GAME_H
