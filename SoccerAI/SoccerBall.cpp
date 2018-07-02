#include "stdafx.h"
#include "SoccerBall.h"


SoccerBall::~SoccerBall()
{
}

glm::vec2 SoccerBall::FuturePosition(float time) const
{
	// x = x0 + v*t + 1/2 * a * t^2;

	glm::vec2 vt = m_Velocity * time;
	glm::vec2 halfat = 0.5f*sFristion*time*time* glm::normalize(m_Velocity);

	glm::vec2 result = m_Pos + vt + halfat;
	return result;
}
