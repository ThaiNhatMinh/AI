#include "stdafx.h"

float Rand()
{
	int a = std::rand() % 4;
	return a/ 4.0f;
}

int Vector2Angle(const glm::vec2 & v)
{
	if (v.x == 0) return (v.y > 0) ? 90 : (v.y == 0) ? 0 : 270;
	else if (v.y == 0) return (v.x >= 0) ? 0 : 180;

	float angle = atanf(v.y / v.x) * 180 / glm::pi<float>();
	if (v.x < 0 && v.y < 0) return angle + 180;
	else if (v.x < 0) return 180 + angle;
	else if (v.y < 0) return 360 + angle;
	return angle;
}
