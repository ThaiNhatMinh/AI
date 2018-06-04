#include "stdafx.h"
#include "Vehicle.h"
#include "SteeringBehavior.h"
extern int m_iWidth, m_iHeight;
Vehicle::Vehicle(const char * name):MovingObject(name), m_Steering(this)
{
}
void Vehicle::OnCreate(GameWorld * world)
{
	m_pWorld = world;
}
void Vehicle::Update(float dt)
{
	MovingObject::Update(dt);
	m_CurrentForce = m_Steering.Calculate();
	m_CurrentAcceleration = m_CurrentForce / m_fMass;

	m_Velocity += m_CurrentAcceleration * dt;

	if (glm::length(m_Velocity) > fMaxSpeed)
	{
		m_Velocity = glm::normalize(m_Velocity) * fMaxSpeed;
	}

	m_Pos += m_Velocity * dt;

	if (m_Pos.x > m_iWidth / 2) m_Pos.x = -m_iWidth / 2;
	else if (m_Pos.x < -m_iWidth / 2) m_Pos.x = m_iWidth / 2;
	if (m_Pos.y > m_iHeight / 2) m_Pos.y = -m_iHeight / 2;
	else if (m_Pos.y < -m_iHeight / 2) m_Pos.y = m_iHeight / 2;

	if (glm::length(m_Velocity) > 0.1)
	{
		m_Front = glm::normalize(m_Velocity);
		m_Right = glm::vec2(m_Front.y, -m_Front.x);
	}
	
	UI(dt);
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
	//std::cout << angle << std::endl;
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
	glColor3f(0, 1, 0);
	glVertex2f(0, 0);
	glVertex2f(m_CurrentForce.x, m_CurrentForce.y);
	glEnd();

	//RenderTarget();
	glPopMatrix();

}

void Vehicle::RenderTarget()
{
	glm::vec2 pos = m_Steering.GetTargetPos();
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glBegin(GL_LINES);
	glVertex2d(10, 10);
	glVertex2d(-10, -10);
	glVertex2d(-10, 10);
	glVertex2d(10, -10);
	glEnd();
	glPopMatrix();
}

void Vehicle::UI(float dt)
{
	ImGui::Begin(GetName().c_str());
	ImGui::SliderFloat("Max Speed", &fMaxSpeed, 100, 400);
	if (ImGui::Button("Reset"))
	{
		Reset();
	}

	if (ImGui::Button("Behvior"))
	{
		m_Steering.SetSteerType((m_Steering.GetSteerType() + 1) % SteerType::SteerNum);
	}
	ImGui::SameLine();
	ImGui::Text(Behavior[m_Steering.GetSteerType()].c_str());
	if (m_Steering.GetSteerType() == SteerType::Arrive)
	{
		if (ImGui::Button("Speed"))
		{
			m_Steering.SetArrriveType((m_Steering.GetArriveType() + 1) % 3);
		}
		ImGui::SameLine();
		ImGui::Text(ArriveTypeS[m_Steering.GetArriveType()].c_str());
	}
	ImGui::End();
}