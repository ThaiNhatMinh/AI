#include "stdafx.h"

float Rand()
{
	int a = std::rand() % 4;
	return a/ 4.0f;
}

glm::vec2 RotateVector(const glm::vec2 & v, float angle)
{
	glm::vec2 r;
	glm::vec2 t = v;
	r.x = t.x * std::cosf(glm::radians(angle)) - t.y * std::sinf(glm::radians(angle));
	r.y = t.x * std::sinf(glm::radians(angle)) + t.y * std::cosf(glm::radians(angle));
	return r;
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

float cross(const glm::vec2 & A, const glm::vec2 & B)
{
	return A.x*B.y - A.y*B.x;
}
bool LineIntersection(const glm::vec2 & A, const glm::vec2 & B, const glm::vec2 & C, const glm::vec2 & D, glm::vec2 & p)
{

	glm::vec2 r = B - A;
	glm::vec2 s = D - C;
	float rxs = cross(r, s);
	float t = cross((D - A), s) /rxs;
	float u = cross((D - A), r) / rxs;

	if (rxs != 0)
	{
		p = A + r * t;
		return true;
	}
	return false;
}
