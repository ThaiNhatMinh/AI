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

glm::vec2 TransfromPoint(const glm::vec2 & p, float angle, const glm::vec2 translate)
{
	glm::vec2 r;
	glm::vec2 t = p;
	r.x = t.x * std::cosf(glm::radians(angle)) - t.y * std::sinf(glm::radians(angle));
	r.y = t.x * std::sinf(glm::radians(angle)) + t.y * std::cosf(glm::radians(angle));
	r += translate;
	return r;
}

glm::vec2 WorldToLocal(const glm::vec2 & p, float angle, const glm::vec2 translate)
{
	glm::vec2 r;
	glm::vec2 t = p + translate;
	

	r.x = t.x * std::cosf(glm::radians(angle)) - t.y * std::sinf(glm::radians(angle));
	r.y = t.x * std::sinf(glm::radians(angle)) + t.y * std::cosf(glm::radians(angle));
	return r;
}
