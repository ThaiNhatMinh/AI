#pragma once

class Wall
{
private:
	glm::vec2 m_from, m_to,m_Normal;
public:
	Wall(const glm::vec2& from, const glm::vec2& to) :m_from(from), m_to(to) {
		glm::vec2 t = glm::normalize(m_to - m_from);
		m_Normal.x = -t.y;
		m_Normal.y = t.x;
	}
	const glm::vec2& From()const { return m_from; }
	const glm::vec2& To() const{ return m_to; }
	const glm::vec2& Normal()const
	{
		return m_Normal;
	}

	void Render()
	{
		glPushMatrix();
		glLoadIdentity();
		glColor3f(0.1, 1.0f, 0.6);
		glLineWidth(2.0f);
		glBegin(GL_LINES);
		glVertex2f(m_from.x, m_from.y);
		glVertex2f(m_to.x, m_to.y);
		glEnd();
		glLineWidth(1.0f);
		glPopMatrix();
	}
};
