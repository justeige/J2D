#pragma once

// TODO add guards

#include "../ECS/ECS.h"

#include "../Components/Camera_Follow_Component.h"
#include "../Components/Transform_Component.h" // TODO into cpp
#include "../Game.h"

class Camera_Movement_System : public System {
public:
	Camera_Movement_System()
	{
		require_component<Camera_Follow_Component>();
		require_component<Transform_Component>();
	}


	void update(SDL_Rect& camera)
	{
		for (auto entity : system_entities()) {
			const auto transform = entity.component<Transform_Component>();
			
			if (transform.position.x + (camera.w / 2) < Game::map_width) {
				camera.x = transform.position.x - (Game::window_width / 2);
			}

			if (transform.position.y + (camera.h / 2) < Game::map_height) {
				camera.y = transform.position.y - (Game::window_height / 2);
			}

			// keep camera rect view inside the screen limits
			camera.x = camera.x < 0 ? 0 : camera.x;
			camera.y = camera.y < 0 ? 0 : camera.y;
			camera.x = camera.x > camera.w ? camera.w : camera.x;
			camera.y = camera.y > camera.h ? camera.h : camera.y;
		}
	}
};
