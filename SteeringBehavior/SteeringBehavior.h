#pragma once
#include <glm/vec2.hpp>

class Vehicle;
enum SteerType
{
	Seek,
	Flee,
	Arrive,
	Pursuit,
	Wander,
	ObstacleAvoidance,
	WallAvoidance,
	Interpose,
	Hide,
	SteerNum
};
enum Deceleration { slow = 3, normal = 2, fast = 1};

static std::vector<std::string> Behavior{ "Seek", "Flee", "Arrive","Pursuit","Wander","ObstacleAvoidance","WallAvoidance","Interpose","Hide" };
static std::vector<std::string> ArriveTypeS{ "Fast", "Normal", "Slow" };

class SteeringBehavior
{
private:
	Vehicle * m_pOwner;
	glm::vec2 m_TargetPos = glm::vec2(0);
	SteerType Type;
	Deceleration ArriveType;
public:
	SteeringBehavior(Vehicle* owner) :m_pOwner(owner) {};
	const glm::vec2& Calculate();
	void RenderDebugUI();
	void RenderDebugObj();
	const glm::vec2& GetTargetPos() {
		return m_TargetPos;
	};

	void SetSteerType(int t) { Type = (SteerType)t; }
	int GetSteerType() { return Type; }
	void SetArrriveType(int t) { ArriveType = (Deceleration)t;  }
	int GetArriveType() { return ArriveType; }
private:
	glm::vec2 Seek(const glm::vec2& target);
	glm::vec2 Flee(const glm::vec2& target);
	glm::vec2 Arrive(const glm::vec2& target, Deceleration type);
	glm::vec2 Pursuit(MovingObject* target);
	glm::vec2 Evade(MovingObject* target); 
	glm::vec2 Wander();
	
private: // Wander param
	float m_fWanderRadius = 30.0f;
	float m_fWanderDistance = 70;
	float m_fWanderJitter = 50.0;
public: // Wander get/set
	float* GetWanderRadius() { return &m_fWanderRadius; }
	void SetWanderRadius(float f) { m_fWanderRadius = f; }

	float* GetWanderDistance() { return &m_fWanderDistance; }
	void SetWanderDistance(float f) { m_fWanderDistance = f; }

	float* GetWadnerJitter() { return &m_fWanderJitter; }
	void SetWanderJitter(float f) { m_fWanderJitter = f; }


private: // ObstacleAvoidance
	float m_fBoxLength;
	float BrakingWeight = 0.5;
	float TurnMultiplier = 1.5f;
	glm::vec2 TempPos;
	glm::vec2 ObstacleAvoidance();

private: // WallAvoidance
	float m_FleelerLength = 40;
	float m_fForceMulti = 50.0f;
	float m_fBaseForce = 50.0f;
	std::vector<glm::vec2> m_Fleelers;
	void CreateFleeler();
	glm::vec2 WallAvoidance();

private: // Interpose
	glm::vec2 Interpose();

private: // Hide
	glm::vec2 GetHidingPosition(const glm::vec2& objPos, float radius, const glm::vec2&posTarget);
	glm::vec2 Hide();

};