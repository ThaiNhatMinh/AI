#pragma once

#include "MovingObject.h"
#include "SteeringBehavior.h"
class GameWorld;
class Vehicle : public MovingObject
{
private:
	GameWorld * m_pWorld;
	SteeringBehavior m_Steering;
public:
	Vehicle(const char* name);
	void OnCreate(GameWorld* world);
	void Update(float dt);
	void Render();

	GameWorld* GetWorld() { return m_pWorld; }

};