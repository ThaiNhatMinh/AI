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
	SteerNum
};
enum Deceleration { slow = 3, normal = 2, fast = 1};

static std::vector<std::string> Behavior{ "Seek", "Flee", "Arrive","Pursuit","Wander" };
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
	float m_fWanderRadius = 15.0f;
	float m_fWanderDistance = 30;
	float m_fWanderJitter = 80.0f;

};