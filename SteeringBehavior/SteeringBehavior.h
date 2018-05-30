#pragma once
#include <glm/vec2.hpp>

class Vehicle;
enum SteerType
{
	Seek,
	Flee,
	Arrive,
	Pursuit,
	SteerNum
};
enum Deceleration { slow = 3, normal = 2, fast = 1};
class SteeringBehavior
{
private:
	Vehicle * m_pOwner;

public:
	SteeringBehavior(Vehicle* owner) :m_pOwner(owner) {};
	const glm::vec2& Calculate();

private:
	glm::vec2 Seek(const glm::vec2& target);
	glm::vec2 Flee(const glm::vec2& target);
	glm::vec2 Arrive(const glm::vec2& target, Deceleration type);
	glm::vec2 Pursuit(MovingObject* target);
};