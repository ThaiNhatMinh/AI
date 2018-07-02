#pragma once
#include "MovingObject.h"
class PlayerBase;
class SoccerBall :	public MovingObject
{
public:
	static float sFristion;  // this is a fake acceleration
public:
	SoccerBall(glm::vec2 pos, float size, float mass, std::vector<Wall>& walls):m_PitchBoundary(walls), MovingObject("Ball"),m_pOwner(nullptr)
	{
		MovingObject::SetPos(pos);
		MovingObject::SetSize(glm::vec2(size, size));
		MovingObject::SetMass(mass);

	}
	virtual ~SoccerBall();


	void Render();
	bool HandleMessage(const Telegram& msg) override{ return 0; }
	void Kick(glm::vec2 direction, float force);

	float TimeMoveToPos(glm::vec2 from, glm::vec2 to, float force)const;
	glm::vec2 FuturePosition(float time)const;

	void Trap(PlayerBase* owner) { m_Velocity = glm::vec2(0); m_pOwner = owner; }
	glm::vec2 OldPos()const { return m_OldPos; }

	void PlaceAtPosition(glm::vec2 pos);
private:
	
	glm::vec2 m_OldPos;

	PlayerBase* m_pOwner;

	const std::vector<Wall>& m_PitchBoundary;

	void TestCollisionWalls(const std::vector<Wall>& walls);

};

