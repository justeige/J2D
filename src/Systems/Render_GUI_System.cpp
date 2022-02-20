#include "Render_GUI_System.h"
#include "../Components/Components.h"

#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>

using namespace ImGui;

void Render_GUI_System::update(Unique<Registry>& registry)
{
	NewFrame();

	if (Begin("Spawn enemies")) {
		static auto x_pos = 0;
		static auto y_pos = 0;
		InputInt("x pos", &x_pos);
		InputInt("y pos", &y_pos);

		static auto x_scale = 0;
		static auto y_scale = 0;
		InputInt("x scale", &x_scale);
		InputInt("y scale", &y_scale);

		static auto x_vel = 0;
		static auto y_vel = 0;
		InputInt("x vel", &x_vel);
		InputInt("y vel", &y_vel);

		static auto health = 100;
		SliderInt("health", &health, 0, 100);

		static auto rotation = 0.0f;
		InputFloat("rotation", &rotation);

		Spacing();

		static auto proj_angle    = 0.0f;
		static auto proj_speed    = 100.0f;
		static auto proj_repeat   = 10;
		static auto proj_duration = 10;
		
		if (CollapsingHeader("Projectile emitter")) {
			InputFloat("angle",  &proj_angle);
			InputFloat("speed",  &proj_speed);
			InputInt("repeat",   &proj_repeat);
			InputInt("duration", &proj_duration);
		}
		Spacing();

		const char* sprites[] = { AID_Tank.c_str(), AID_Truck.c_str() };

		if (Button("Create new enemy")) {
			auto enemy = registry->create_entity();

			const auto proj_vel_x = cos(proj_angle) * proj_speed;
			const auto proj_vel_y = sin(proj_angle) * proj_speed;

			enemy.group("enemies");
			enemy.add_component<Transform_Component>(Vec2(x_pos, y_pos), Vec2(x_scale, y_scale), rotation);
			enemy.add_component<Rigid_Body_Component>(Vec2(x_vel, y_vel));
			enemy.add_component<Sprite_Component>(AID_Tank, 32, 32, 1);
			enemy.add_component<Box_Collider_Component>(32, 32);
			enemy.add_component<Projectile_Emitter_Component>(
				Vec2{ proj_vel_x, proj_vel_y }, 
				proj_repeat * 1000, 
				proj_duration * 1000, 
				10, 
				false
			);
			enemy.add_component<Health_Component>(health);

			// reset 
			x_pos = y_pos = x_scale = y_scale = rotation = proj_angle = 0;
			proj_repeat = proj_duration = 10;
			proj_speed = 100;
			health = 100;
		}
	}
	End();

	Render();
	ImGuiSDL::Render(GetDrawData());
}
