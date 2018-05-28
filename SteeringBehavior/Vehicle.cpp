#include "stdafx.h"
#include "Vehicle.h"
#include "SteeringBehavior.h"

Vehicle::Vehicle(const char * name):MovingObject(name), m_Steering(this)
{
}
void Vehicle::OnCreate(GameWorld * world)
{
	m_pWorld = world;
}
void Vehicle::Update(float dt)
{
	m_CurrentForce = m_Steering.Calculate();
	m_CurrentAcceleration = m_CurrentForce / m_fMass;

	m_Velocity += m_CurrentAcceleration * dt;

	if (glm::length(m_Velocity) > fMaxSpeed)
	{
		m_Velocity = glm::normalize(m_Velocity) * fMaxSpeed;
	}

	m_Pos += m_Velocity * dt;

	if (glm::length(m_Velocity) > 1)
	{
		m_Front = glm::normalize(m_Velocity);
		m_Right = glm::vec2(m_Front.y, -m_Front.x);
	}
	
}
int Vector2Angle(const glm::vec2& v)
{
	if (v.x == 0) return (v.y > 0) ? 90 : (v.y == 0) ? 0 : 270;
	else if (v.y == 0) return (v.x >= 0) ? 0 : 180;
	
	float angle = atanf(v.y / v.x) * 180 / glm::pi<float>();
	if (v.x < 0 && v.y < 0) return angle + 180;
	else if (v.x < 0) return 180 + angle;
	else if (v.y < 0) return 360 + angle;
	return angle;
}
void Vehicle::Render()
{
	
	float angle = 0;
	glPushMatrix();
	glLoadIdentity();
	if (m_Velocity != glm::vec2(0))
	{
		glm::vec2 direction = glm::normalize(m_Velocity);
		angle = Vector2Angle(m_Velocity) - 90;
	}
	// PI/180
	//angle = angle * 180 / glm::pi<float>();
	//
	std::cout << angle << std::endl;
	glTranslatef(m_Pos.x, m_Pos.y, 0);
	glPushMatrix();
	glRotatef(angle, 0, 0, 1);

	glColor3f(1, 1, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0, 50);
	glVertex2f(-15, 0);
	glVertex2f(15, 0);
	glEnd();
	glPopMatrix();
	
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(m_Velocity.x, m_Velocity.y);
	glEnd();
	glPopMatrix();
}

