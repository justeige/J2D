#ifndef COMPONENT_OPERATIONS_H
#define COMPONENT_OPERATIONS_H

#include "Sprite_Component.h"
#include "Transform_Component.h"
#include "Rigid_Body_Component.h"
#include "Animation_Component.h"
#include "Box_Collider_Component.h"

#include <SDL.h>

inline SDL_Rect create_rect_from(Sprite_Component sprite, Transform_Component transform)
{
	return {
		static_cast<int>(transform.position.x),
		static_cast<int>(transform.position.y),
		static_cast<int>(sprite.width * transform.scale.x),
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

#endif
