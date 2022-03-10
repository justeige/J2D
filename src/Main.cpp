#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <glm/glm.hpp>

#include <imgui/imgui.h>


#include "Game.h"

//void test_lua()
//{
//	sol::state lua;
//	lua.open_libraries(sol::lib::base);
//	lua.script_file("./assets/scripts/level1.lua");
//
//	int some_var = lua["some_var"];
//
//	sol::table config = lua["config"];
//
//	std::cout << some_var << '\n';
//}

int main(int argc, char** argv) 
{
	try
	{
		Game game;

		game.init();
		game.run();
		game.destroy();

	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
	}

    return 0;
}
