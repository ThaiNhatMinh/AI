#include "stdafx.h"
#include "Vehicle.h"


const glm::vec2 & SteeringBehavior::Calculate()
{
	//GameWorld* pWorld = m_pOwner->GetWorld();
	MovingObject* pTarget = m_pOwner->GetTarget();
	glm::vec2 force;
	if(Type==SteerType::Seek) force = Seek(pTarget->GetPos());
	else if(Type==SteerType::Flee) force = Flee(pTarget->GetPos());
	else if (Type == SteerType::Arrive) force = Arrive(pTarget->GetPos(), (Deceleration)(ArriveType+1));
	else if (Type == SteerType::Pursuit) force = Pursuit(pTarget);
	else if (Type == SteerType::Wander) force = Wander();
	return force;
}
glm::vec2 SteeringBehavior::Seek(const glm::vec2 & target)
{
	m_TargetPos = target;
	glm::vec2 DesiredVelocity = glm::normalize(target - m_pOwner->GetPos())* m_pOwner->GetMaxSpeed();
	return (DesiredVelocity - m_pOwner->GetVelocity());
}
glm::vec2 SteeringBehavior::Flee(const glm::vec2 & target)
{
	m_TargetPos = glm::vec2(10000,10000);
	const double SafeRange = 500 ;
	if (glm::distance(target, m_pOwner->GetPos()) > SafeRange) return glm::vec2(0);

	glm::vec2 DesiredVelocity = glm::normalize(m_pOwner->GetPos() - target)* m_pOwner->GetMaxSpeed();
	return (DesiredVelocity - m_pOwner->GetVelocity());

}

glm::vec2 SteeringBehavior::Arrive(const glm::vec2 & target, Deceleration type)
{
	m_TargetPos = target;
	glm::vec2 ToTarget = target - m_pOwner->GetPos();

	float Distance = glm::length(ToTarget);
	if (Distance > 0.9)
	{
		const double DecelerationTweaker = 0.3;
		double speed = Distance / ((double)type * DecelerationTweaker);
		speed = glm::min(speed, (double)m_pOwner->GetMaxSpeed());

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

	float FutureTime = glm::length(ToTarget) / (m_pOwner->GetMaxSpeed() + glm::length(target->GetVelocity()));
	
	m_TargetPos = target->GetPos() + target->GetVelocity()*FutureTime;
	return Seek(m_TargetPos);
}

glm::vec2 SteeringBehavior::Evade(MovingObject * target)
{
	glm::vec2 ToTarget = target->GetPos() - m_pOwner->GetPos();
	float RelateFront = glm::dot(target->GetFront(), m_pOwner->GetFront());
	if (glm::dot(ToTarget, m_pOwner->GetFront()) > 0 && RelateFront < -0.95) return Seek(target->GetPos());

	float FutureTime = glm::length(ToTarget) / (m_pOwner->GetMaxSpeed() + glm::length(target->GetVelocity()));

	m_TargetPos = target->GetPos() + target->GetVelocity()*FutureTime;
	return Flee(m_TargetPos);
}

glm::vec2 SteeringBehavior::Wander()
{
	auto v  = glm::vec2(Rand()* m_fWanderJitter, Rand()*m_fWanderJitter);
	m_TargetPos += v;
	m_TargetPos = glm::normalize(m_TargetPos);
	m_TargetPos *= m_fWanderRadius;
	m_TargetPos += glm::vec2(0, m_fWanderDistance);

	float angle = Vector2Angle(m_pOwner->GetVelocity());
	glm::vec2 t = m_TargetPos;
	m_TargetPos.x = t.x * std::cosf(glm::radians(angle)) - t.y * std::sinf(glm::radians(angle));
	m_TargetPos.y = t.x * std::sinf(glm::radians(angle)) + t.y * std::cosf(glm::radians(angle));
	m_TargetPos += m_pOwner->GetPos();

	return m_TargetPos - m_pOwner->GetPos();

}