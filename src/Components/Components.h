#ifndef COMPONENT_OPERATIONS_H
#define COMPONENT_OPERATIONS_H

#include "Sprite_Component.h"
#include "Transform_Component.h"
#include "Rigid_Body_Component.h"
#include "Animation_Component.h"
#include "Box_Collider_Component.h"
#include "Keyboard_Controlled_Component.h"
#include "Camera_Follow_Component.h"
#include "Project_Emitter_Component.h"
#include "Health_Component.h"
#include "Projectile_Component.h"
#include "Text_Label_Component.h"

#include <SDL.h>

inline SDL_Rect create_rect_from(Sprite_Component sprite, Transform_Component transform, SDL_Rect camera)
{
	return {
		static_cast<int>(transform.position.x - (sprite.is_fixed ? 0 : camera.x)),
		static_cast<int>(transform.position.y - (sprite.is_fixed ? 0 : camera.y)),
		static_cast<int>(sprite.width  * transform.scale.x),
		static_cast<int>(sprite.height * transform.scale.y)
	};
}

inline SDL_Rect create_rect_from(Transform_Component transform, Box_Collider_Component collider)
{
	return {
		static_cast<int>(transform.position.x),
		static_cast<int>(transform.position.y),
		static_cast<int>(collider.width),
		static_cast<int>(collider.height)
	};
}

inline Vec2 direction_of_projectile(Projectile_Emitter_Component projectile_emitter, Rigid_Body_Component rigid_body)
{
	auto projectile_velocity = projectile_emitter.projectile_velocity;
	auto direction_x = 0;
	auto direction_y = 0;

	if (rigid_body.velocity.x > 0) direction_x = +1;
	if (rigid_body.velocity.x < 0) direction_x = -1;
	if (rigid_body.velocity.y > 0) direction_y = +1;
	if (rigid_body.velocity.y < 0) direction_y = -1;

	projectile_velocity.x = projectile_emitter.projectile_velocity.x * direction_x;
	projectile_velocity.y = projectile_emitter.projectile_velocity.y * direction_y;

	return projectile_velocity;
}

#endif
