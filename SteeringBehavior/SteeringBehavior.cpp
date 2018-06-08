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
	else if (Type == SteerType::ObstacleAvoidance) force = ObstacleAvoidance();
	return force;
}
void SteeringBehavior::RenderDebugUI()
{
	
	glPushMatrix();
	glTranslatef(m_TargetPos.x, m_TargetPos.y, 0);
	glBegin(GL_LINES);
	glVertex2d(10, 10);
	glVertex2d(-10, -10);
	glVertex2d(-10, 10);
	glVertex2d(10, -10);
	glEnd();
	glPopMatrix();

	if (ImGui::Button("Behvior"))
	{
		Type = (SteerType)((Type + 1) % SteerType::SteerNum);
	}
	ImGui::SameLine();
	ImGui::Text(Behavior[Type].c_str());
	if (Type == SteerType::Arrive)
	{
		if (ImGui::Button("Speed"))
		{
			SetArrriveType((GetArriveType() + 1) % 3);
		}
		ImGui::SameLine();
		ImGui::Text(ArriveTypeS[GetArriveType()].c_str());
	}
	else if (Type == SteerType::Wander)
	{
		ImGui::SliderFloat("Radius ", GetWanderRadius(), 10, 100);
		ImGui::SliderFloat("Distance ", GetWanderDistance(), 50, 150);
		ImGui::SliderFloat("Jitter ", GetWadnerJitter(), 10, 100);
	}
	else if (Type == SteerType::ObstacleAvoidance)
	{
		ImGui::SliderFloat("BrakingWeight", &BrakingWeight, 0.1, 2.0f);
		ImGui::SliderFloat("TurnMultiplier", &TurnMultiplier, 1.0f, 2.0f);

	}
}
void SteeringBehavior::RenderDebugObj()
{
	if (Type == SteerType::ObstacleAvoidance)
	{
		glBegin(GL_LINE_LOOP);
		glColor3f(1.0f, 0.1f, 0.5f);
		glVertex2f(m_pOwner->GetWidth()*1.5 / 2, 0);
		glVertex2f(m_pOwner->GetWidth()*1.5 / 2, m_fBoxLength);
		glVertex2f(-m_pOwner->GetWidth()*1.5 / 2, m_fBoxLength);
		glVertex2f(-m_pOwner->GetWidth()*1.5 / 2, 0);
		glEnd();

		glPushMatrix();
		glLoadIdentity();
		glPointSize(2.0f);
		glBegin(GL_POINTS);
		glVertex2f(TempPos.x, TempPos.y);
		glEnd();
		glPointSize(1.0f);
		glPopMatrix();
	}
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

	float angle = Vector2Angle(m_pOwner->GetVelocity()) - 90;
	/*glm::vec2 t = m_TargetPos;
	m_TargetPos.x = t.x * std::cosf(glm::radians(angle)) - t.y * std::sinf(glm::radians(angle));
	m_TargetPos.y = t.x * std::sinf(glm::radians(angle)) + t.y * std::cosf(glm::radians(angle));
	m_TargetPos += m_pOwner->GetPos();*/
	
	m_TargetPos = TransfromPoint(m_TargetPos, angle, m_pOwner->GetPos());

	/*glm::mat3 ts;
	ts[0] = glm::vec3(std::cosf(glm::radians(angle)), -std::sinf(glm::radians(angle)),0.0f);
	ts[1] = glm::vec3(std::sinf(glm::radians(angle)), std::cosf(glm::radians(angle)), 0.0f);
	ts[2] = glm::vec3(0, 0, 1);
	glm::mat3 tt;
	tt[2] = glm::vec3(m_pOwner->GetPos(), 1.0f);
	m_TargetPos = ts * tt*glm::vec3(m_TargetPos, 0);*/

	/*glm::mat3 ts;
	ts[0] = glm::vec3(m_pOwner->GetFront(),0);
	ts[1] = glm::vec3(m_pOwner->GetRight(),0);
	m_TargetPos = ts * glm::vec3(m_TargetPos,0);
	m_TargetPos += m_pOwner->GetPos();*/

	//return m_TargetPos - m_pOwner->GetPos();
	return Seek(m_TargetPos);
}

glm::vec2 SteeringBehavior::ObstacleAvoidance()
{
	TempPos = glm::vec2(0);
	GameWorld* pWorld = m_pOwner->GetWorld();
	auto& ObstacleList = pWorld->GetObstacle();
	m_fBoxLength = m_pOwner->GetHeight() + (glm::length(m_pOwner->GetVelocity())/m_pOwner->GetMaxSpeed())*m_pOwner->GetHeight();

	Obstacle* CloestIntersecting = nullptr;
	float Distance = 0xffffffff;
	glm::vec2 localPos;

	for (int i = 0; i < ObstacleList.size(); i++)
	{
		float dis = glm::length(ObstacleList[i]->GetPos() - m_pOwner->GetPos());
		if (dis < m_fBoxLength + ObstacleList[i]->GetRadius())
		{
			TempPos = WorldToLocal(ObstacleList[i]->GetPos(),90- Vector2Angle(m_pOwner->GetVelocity()), -m_pOwner->GetPos());
			

			if (TempPos.y > 0) // in front of vehicle
			{
				float ExpanRadius = ObstacleList[i]->GetRadius() + m_pOwner->GetWidth()*1.5 / 2;
				if (std::fabs(TempPos.x) < ExpanRadius)
				{
					float sqrtPart = std::sqrt(ExpanRadius*ExpanRadius - TempPos.x*TempPos.x);
					float r = TempPos.y - sqrtPart;
					if (r <= 0) r = TempPos.y + sqrtPart;

					if (r < Distance)
					{
						Distance = r;
						CloestIntersecting = ObstacleList[i].get();
						localPos = TempPos;
					}
				}
			}
		}
	}

	glm::vec2 r;
	if (CloestIntersecting)
	{
		float multiplier = 100.0f + TurnMultiplier*(m_fBoxLength - localPos.y) / m_fBoxLength;

		r.x = (CloestIntersecting->GetRadius() - localPos.x)*multiplier;
		r.y = (CloestIntersecting->GetRadius() - localPos.y)*BrakingWeight;
		r = TransfromPoint(r, Vector2Angle(m_pOwner->GetVelocity()) - 90, m_pOwner->GetPos());
		m_TargetPos = glm::normalize(r) * m_pOwner->GetMaxSpeed();
		return m_TargetPos;
	}
	return Wander();
}

