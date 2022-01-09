#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <glm/glm.hpp>

#include <imgui/imgui.h>

#include <sol/sol.hpp>

#include "Game.h"

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
