#include "stdafx.h"
#include "MovingObject.h"





MovingObject::MovingObject(const char* name):GameObject(name),m_Velocity(0),m_Front(0,1),m_Right(1,0),m_fMass(0),m_Pos(0), m_Size(30, 50)
{
}

void MovingObject::Update(float dt)
{
	
}

void MovingObject::Reset()
{
	fMaxSpeed = 200;
	fMaxForce = 200;
	this->SetPos(glm::vec2(0));
	this->SetVelocity(glm::vec2(0));
}
void MovingObject::OnCreate(GameWorld * world)
{
	m_pWorld = world;
}