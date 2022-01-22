#ifndef KEY_PRESSED_EVENT_H
#define KEY_PRESSED_EVENT_H

#include "../ECS/Entity.h"
#include "../Event_Bus/Event.h"

#include <SDL.h>

struct Key_Pressed_Event : public Event {
	SDL_Keycode key_code;

	Key_Pressed_Event(SDL_Keycode code) : key_code{ code }
	{}

};
#endif // !KEY_PRESSED_EVENT_H
