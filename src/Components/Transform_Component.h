#pragma once

#include <glm/glm.hpp>

struct Transform_Component {
	glm::vec2 position;
	glm::vec2 scale;
	double rotation;

	Transform_Component(glm::vec2 pos = glm::vec2{ 0,0 }, glm::vec2 scale = glm::vec2{ 1,1 }, double rotation = 0)
		: position{pos}, scale{scale}, rotation{rotation}
	{
	}
};