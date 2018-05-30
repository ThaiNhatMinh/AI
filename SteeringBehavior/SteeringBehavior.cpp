#include "stdafx.h"
#include "Vehicle.h"
extern int Type;
extern int ArriveType;
extern float fMaxSpeed;
const glm::vec2 & SteeringBehavior::Calculate()
{
	GameWorld* pWorld = m_pOwner->GetWorld();
	MovingObject* pTarget = pWorld->GetTarget();
	glm::vec2 force;
	if(Type==SteerType::Seek) force = Seek(pTarget->GetPos());
	else if(Type==SteerType::Flee) force = Flee(pTarget->GetPos());
	else if (Type == SteerType::Arrive) force = Arrive(pTarget->GetPos(), (Deceleration)(ArriveType+1));
	else if (Type == SteerType::Pursuit) force = Pursuit(pTarget);
	return force;
}
glm::vec2 SteeringBehavior::Seek(const glm::vec2 & target)
{
	glm::vec2 DesiredVelocity = glm::normalize(target - m_pOwner->GetPos())* fMaxSpeed;
	return (DesiredVelocity - m_pOwner->GetVelocity());
}
glm::vec2 SteeringBehavior::Flee(const glm::vec2 & target)
{
	const double SafeRange = 50 ;
	if (glm::distance(target, m_pOwner->GetPos()) > SafeRange) return glm::vec2(0);

	glm::vec2 DesiredVelocity = glm::normalize(m_pOwner->GetPos() - target)* fMaxSpeed;
	return (DesiredVelocity - m_pOwner->GetVelocity());
}

glm::vec2 SteeringBehavior::Arrive(const glm::vec2 & target, Deceleration type)
{
	glm::vec2 ToTarget = target - m_pOwner->GetPos();

	float Distance = glm::length(ToTarget);
	if (Distance > 0.9)
	{
		const double DecelerationTweaker = 0.3;
		double speed = Distance / ((double)type * DecelerationTweaker);
		speed = glm::min(speed, (double)fMaxSpeed);

		// this actully is ToTarget*type*DeclerationTweaker
		// speed just to check if it higher than MaxSpeed
		glm::vec2 DesiredVel = ToTarget * float(speed / Distance); 
		return DesiredVel - m_pOwner->GetVelocity();

	}
	return glm::vec2(0);
}

glm::vec2 SteeringBehavior::Pursuit(MovingObject * target)
{
	glm::vec2 ToTarget = target->GetPos() - m_pOwner->GetPos();
	float RelateFront = glm::dot(target->GetFront(), m_pOwner->GetFront());
	if (glm::dot(ToTarget, m_pOwner->GetFront()) > 0 && RelateFront < -0.95) return Seek(target->GetPos());

	float FutureTime = glm::length(ToTarget) / (fMaxSpeed + glm::length(target->GetVelocity()));
	
	return Seek(target->GetPos() + target->GetVelocity()*FutureTime);
}
