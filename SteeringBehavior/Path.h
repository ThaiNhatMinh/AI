#pragma once

class Path
{
private:
	std::list<glm::vec2> m_WayPoint;
	std::list<glm::vec2>::iterator m_CurrentPoint;

	bool m_bLoop;

public:
	Path() :m_bLoop(false) {}
	Path(int num, glm::vec2 min, glm::vec2 max, bool loop)
	{
		CreateRandomWayPoint(num, min, max);
		m_CurrentPoint = m_WayPoint.begin();
		m_bLoop = loop;
	}

public:
	void CreateRandomWayPoint(int num, glm::vec2 min, glm::vec2 max);
	glm::vec2 GetCurrentWayPoint()const
	{
		return *m_CurrentPoint;
	}

	bool IsFinished() { return m_CurrentPoint == m_WayPoint.end(); }
	void SetNextWayPoint();

	void SetLoop(bool l) { m_bLoop = l; }
	std::list<glm::vec2> GetPath();

	void Render();
};