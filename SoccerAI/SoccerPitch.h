#pragma once

class SoccerBall;
class SoccerTeam;
class Goal;
class Region;

class SoccerPitch
{
public:
	SoccerPitch();
	~SoccerPitch();

	void Update(float dt);
	void Render();
public:
	SoccerBall * m_pBall;
	SoccerTeam * m_pRedTeam;
	SoccerTeam * m_pBlueTeam;
	Goal * m_pRedGoal;
	Goal * m_pBlueGoal;

	std::vector<Wall> m_vWalls;

	Region * m_pPlayingArea;
	std::vector<Region*> m_vRegions;

	bool m_bGameOn;
	bool m_bBallKeeperHasBall;

	
};

