#pragma once
#include "GameObject.h"
#include <glm/vec2.hpp>

class GameWorld;
class MovingObject: public GameObject
{
protected:
	glm::vec2 m_Pos;
	glm::vec2 m_Velocity;
	glm::vec2 m_Front;
	glm::vec2 m_Right;
	glm::vec2 m_CurrentForce;
	glm::vec2 m_CurrentAcceleration;
	float m_fMass;
	GameWorld * m_pWorld;
	MovingObject* m_pTarget = nullptr;
	float fMaxSpeed = 200;
	float fMaxForce = 150;
	float fMaxTurnRate = 10;

public:
	MovingObject(const char* name);
	virtual ~MovingObject() = default;
	void OnCreate(GameWorld* world);
	virtual void Update(float dt);
	const glm::vec2& GetVelocity() { return m_Velocity; }
	void SetVelocity(const glm::vec2& vel) { m_Velocity = vel; }
	const glm::vec2& GetFront() { return m_Front; }
	const glm::vec2& GetRight() { return m_Right; }
	float GetMass() { return m_fMass; }
	void SetMass(float m) { m_fMass = m; }

	
	const glm::vec2& GetPos() { return m_Pos; }
	void SetPos(const glm::vec2& p) { m_Pos = p; }

	void Reset();

	float GetMaxSpeed() { return fMaxSpeed; }
	float GetMaxForce() { return fMaxForce; }
	
	void SetTarget(MovingObject* obj) { m_pTarget = obj; }
	MovingObject* GetTarget() { return m_pTarget; }
};