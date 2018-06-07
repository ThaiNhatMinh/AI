#pragma once


float Rand();


int Vector2Angle(const glm::vec2& v);

glm::vec2 TransfromPoint(const glm::vec2& p, float angle, const glm::vec2 translate);
glm::vec2 WorldToLocal(const glm::vec2& p, float angle, const glm::vec2 translate);