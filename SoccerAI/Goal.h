#pragma once
class Goal
{
public:
	Goal(glm::vec2 left, glm::vec2 right) :m_LeftPos(left), m_RightPos(right), m_Center((left + right) / 2.0f), m_iNumScore(0)
	{
		m_Facing = glm::normalize(left - right);
		m_Facing = glm::vec2(m_Facing.y, -m_Facing.x);
	}
	~Goal();

	// return true if the ball has crossed goal line and incements m_iNumScore
	inline bool Scored(const SoccerBall* ball);
private:
	glm::vec2 m_LeftPos, m_RightPos;
	glm::vec2 m_Facing;
	glm::vec2 m_Center;

	int m_iNumScore;


};

