#pragma once
#include <glm/vec2.hpp>

class Vehicle;
enum SteerType
{
	Seek = 1,
	Flee = 2,
	Arrive = 4,
	Pursuit = 8,
	Wander = 16,
	ObstacleAvoidance = 32,
	WallAvoidance = 64,
	Interpose = 128,
	Hide = 256,
	FollowPath = 512,
	OffsetPursut = 1024,
	SteerNum = 2048
};
enum Deceleration { slow = 3, normal = 2, fast = 1};

static std::vector<std::string> ArriveTypeS{ "Fast", "Normal", "Slow" };

static const char* GetBehaviorName(SteerType type)
{
	switch (type)
	{
	case Seek:
		return "Seek";
		break;
	case Flee:
		return "Flee";
		break;
	case Arrive:
		return "Arrive";
		break;
	case Pursuit:
		return "Pursuit";
		break;
	case Wander:
		return "Wander";
		break;
	case ObstacleAvoidance:
		return "ObstacleAvoidance";
		break;
	case WallAvoidance:
		return "WallAvoidance";
		break;
	case Interpose:
		return "Interpose";
		break;
	case Hide:
		return "Hide";
		break;
	case FollowPath:
		return "FollowPath";
		break;
	case OffsetPursut:
		return "OffsetPursut";
		break;
	case SteerNum:
	default:
		return "Unknow";
		break;
	}
}
class SteeringBehavior
{
private:
	glm::vec2 m_CurrentForce;
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
	bool AccumulateForce(glm::vec2& force, const glm::vec2& ForcetoAdd);
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

private: // Path following
	float m_fWayPointSeekDis = 5; 
	glm::vec2 FollowPath();

private: // Offset Pursut
	glm::vec2 m_Offset;
	MovingObject *m_pTarget = nullptr;
	glm::vec2 OffsetPursut();
public:
	void SetTarget(MovingObject* pTarget) { m_pTarget = pTarget; }
	void SetOffset(const glm::vec2 offset) { m_Offset = offset; }
};