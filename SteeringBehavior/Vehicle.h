#pragma once

#include "MovingObject.h"
#include "SteeringBehavior.h"
class GameWorld;
class Vehicle : public MovingObject
{
private:
	
	SteeringBehavior m_Steering;
	glm::vec2 m_Size;
public:
	Vehicle(const char* name);
	
	void UI(float dt);
	void Update(float dt);
	void Render();

	GameWorld* GetWorld() { return m_pWorld; }
	SteeringBehavior* GetSteerBehavior() {
		return &m_Steering;
	};

	float GetHeight() { return m_Size.y; }
	float GetWidth() { return m_Size.x; }
};