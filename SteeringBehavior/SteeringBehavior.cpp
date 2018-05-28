#include "stdafx.h"
#include "Vehicle.h"
extern int Type;
const glm::vec2 & SteeringBehavior::Calculate()
{
	GameWorld* pWorld = m_pOwner->GetWorld();
	MovingObject* pTarget = pWorld->GetTarget();
	glm::vec2 force;
	if(Type==SteerType::Seek) force = Seek(pTarget->GetPos());
	else if(Type==SteerType::Flee) force = Flee(pTarget->GetPos());
	//return glm::vec2(0);
	return force;
}
glm::vec2 SteeringBehavior::Seek(const glm::vec2 & target)
{
	glm::vec2 DesiredVelocity = glm::normalize(target - m_pOwner->GetPos())* fMaxSpeed;
	return (DesiredVelocity - m_pOwner->GetVelocity());
}
glm::vec2 SteeringBehavior::Flee(const glm::vec2 & target)
{
	glm::vec2 DesiredVelocity = glm::normalize(m_pOwner->GetPos() - target)* fMaxSpeed;
	return (DesiredVelocity - m_pOwner->GetVelocity());
}