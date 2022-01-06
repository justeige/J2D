#include "Animation_System.h"
#include "../Components/Components.h"

Animation_System::Animation_System()
{
	require_component<Sprite_Component>();
	require_component<Animation_Component>();
}

void Animation_System::update()
{
	for (auto entity : system_entities()) {
		auto& animation = entity.component<Animation_Component>();
		auto& sprite    = entity.component<Sprite_Component>();

		animation.current_frame = (
			(SDL_GetTicks() - animation.start_time)
			* animation.frame_rate_speed / 1000) 
			% animation.num_frames;

		sprite.src_rect.x = animation.current_frame * sprite.width;
	}
}