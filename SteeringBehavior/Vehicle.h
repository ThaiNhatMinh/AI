#pragma once

#include "MovingObject.h"
#include "SteeringBehavior.h"
class GameWorld;
class Vehicle : public MovingObject
{
private:
	
	SteeringBehavior m_Steering;
	bool m_bRenderUI = false;
public:
	Vehicle(const char* name);
	
	void UI(float dt);
	void Update(float dt);
	void Render();
	void RenderUI() {
		m_bRenderUI = !m_bRenderUI;
	};
	GameWorld* GetWorld() { return m_pWorld; }
	SteeringBehavior* GetSteerBehavior() {
		return &m_Steering;
	};

	
};