#include "stdafx.h"
#include "Target.h"

Target::Target(const char* name):MovingObject(name)
{
}

void Target::Render()
{
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(m_Pos.x, m_Pos.y, 0);
	glLineWidth(3.0);
	glColor3f(1, 0, 1);
	int w = 15;
	glBegin(GL_LINE_LOOP);
	glVertex2d(w, w);
	glVertex2d(-w, w);
	glVertex2d(-w, -w);
	glVertex2d(w, -w);
	glEnd();
	glLineWidth(1.0);
	glPopMatrix();
}
