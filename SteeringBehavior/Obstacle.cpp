#include "stdafx.h"

void Obstacle::Render()
{
	glPushMatrix();
	glColor3f(0.5, 0.1, 1);
	glTranslatef(m_Pos.x, m_Pos.y, 0);
	glBegin(GL_POINTS);
	glVertex2f(0, 0);
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 360; i += 5)
	{
		float x = std::cosf(glm::radians(float(i)))* m_fRadius;
		float y = std::sinf(glm::radians(float(i)))* m_fRadius;
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}
