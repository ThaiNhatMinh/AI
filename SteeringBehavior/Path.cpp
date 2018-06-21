#include "stdafx.h"

void Path::CreateRandomWayPoint(int num, glm::vec2 min, glm::vec2 max)
{
	glm::vec2 W = max - min;

	for (int i = 0; i < num; i++)
	{
		glm::vec2 p;
		
		p.x = std::rand() %(int)W.x + min.x;
		p.y = std::rand() % (int)W.y + min.y;
		m_WayPoint.push_back(p);
	}
}

void Path::SetNextWayPoint()
{
	m_CurrentPoint++;
	if (m_CurrentPoint == m_WayPoint.end() && m_bLoop) m_CurrentPoint = m_WayPoint.begin();
	
}

std::list<glm::vec2> Path::GetPath()
{
	return m_WayPoint;
}

void Path::Render()
{
	glPushMatrix();
	glLoadIdentity();
	if (m_bLoop) glBegin(GL_LINE_LOOP);
	else glBegin(GL_LINE_STRIP);
	glColor3f(0.4, 1.0f, 0.6f);
	for (auto& el : m_WayPoint) glVertex2f(el.x, el.y);
	glEnd();

	glBegin(GL_POINT);
	glColor3f(1.0, 1.0f, 0.6f);
	glPointSize(2.0f);
	for (auto& el : m_WayPoint) glVertex2f(el.x, el.y);
	glEnd();
	glPointSize(1.0f);
	glPopMatrix();
}
