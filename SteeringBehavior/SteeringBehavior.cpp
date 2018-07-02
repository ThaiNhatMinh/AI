#include "stdafx.h"
#include "Vehicle.h"

float SteeringBehavior::m_fAlignmentWeight = 1.0f;
float SteeringBehavior::m_fCohensionWeight = 1.0f;
float SteeringBehavior::m_fSeparationWeight = 1.0f;
float SteeringBehavior::m_fViewDistance = 40.0f;
const glm::vec2 & SteeringBehavior::Calculate()
{
	//GameWorld* pWorld = m_pOwner->GetWorld();
	MovingObject* pTarget = m_pOwner->GetTarget();
	glm::vec2 force;
	m_CurrentForce = glm::vec2(0);
	/*if (Type == SteerType::Seek)
	{
		if(pTarget)	force = Seek(pTarget->GetPos());
		else force = glm::vec2(0);
	}
	else if(Type==SteerType::Flee) force = Flee(pTarget->GetPos());
	else if (Type == SteerType::Arrive) force = Arrive(pTarget->GetPos(), (Deceleration)(ArriveType+1));
	else if (Type == SteerType::Pursuit) force = Pursuit(pTarget);
	
	else if (Type == SteerType::ObstacleAvoidance) force = ObstacleAvoidance();
	else if (Type == SteerType::WallAvoidance) force = WallAvoidance();
	else if (Type == SteerType::Interpose) force = Interpose();
	else if (Type == SteerType::Hide) force = Hide();
	else if (Type == SteerType::FollowPath) force = FollowPath();
	else if (Type == SteerType::OffsetPursut) force = OffsetPursut();*/

	
	if (IsActive(SteerType::Wander))
	{
		force = Wander();
		if (!AccumulateForce(m_CurrentForce, force)) return m_CurrentForce;
	}
	
	if (IsActive(SteerType::WallAvoidance))
	{
		force = ObstacleAvoidance();
		if (!AccumulateForce(m_CurrentForce, force)) return m_CurrentForce;
	}
	if (IsActive(SteerType::ObstacleAvoidance))
	{
		force = ObstacleAvoidance();
		if (!AccumulateForce(m_CurrentForce, force)) return m_CurrentForce;
	}
	if (IsActive(SteerType::Group))
	{
		force = Group();
		if (!AccumulateForce(m_CurrentForce, force)) return m_CurrentForce;
	}
	return m_CurrentForce;
}
void SteeringBehavior::RenderDebugUI()
{
	static bool wander = IsActive(SteerType::Wander);
	static float wanderW = 1.0f;
	if (ImGui::Checkbox(GetBehaviorName(SteerType::Wander), &wander))
	{
		if(wander) Type = Type | SteerType::Wander;
		else Type = Type & (~SteerType::Wander);
		
	}
	if (wander)
	{
		ImGui::SliderFloat("Radius ", &m_fWanderRadius, 10, 100);
		ImGui::SliderFloat("Distance ", &m_fWanderDistance, 50, 150);
		ImGui::SliderFloat("Jitter ", &m_fWanderJitter, 10, 100);
	}

	static bool group = IsActive(SteerType::Group);
	if (ImGui::Checkbox(GetBehaviorName(SteerType::Group), &group))
	{
		if (group) Type = Type | SteerType::Group;
		else Type = Type & (~SteerType::Group);

	}
	if (group)
	{
		ImGui::SliderFloat("Separation Weight ", &m_fSeparationWeight, 0, 10);
		ImGui::SliderFloat("Alignment Weight ", &m_fAlignmentWeight, 0, 10);
		ImGui::SliderFloat("Cohesion Weight ", &m_fCohensionWeight, 0, 10);
		ImGui::SliderFloat("View Distance ", &m_fViewDistance, 10, 100);
	}

	static bool obsAvoid = IsActive(SteerType::ObstacleAvoidance);
	if (ImGui::Checkbox(GetBehaviorName(SteerType::ObstacleAvoidance), &obsAvoid))
	{
		if (obsAvoid) Type = Type | SteerType::ObstacleAvoidance;
		else Type = Type & (~SteerType::ObstacleAvoidance);

	}
	if (obsAvoid)
	{
		ImGui::SliderFloat("BrakingWeight", &BrakingWeight, 0.1, 2.0f);
		ImGui::SliderFloat("TurnMultiplier", &TurnMultiplier, 1.0f, 2.0f);

	}
	static bool wallAvoid = IsActive(SteerType::WallAvoidance);
	if (ImGui::Checkbox(GetBehaviorName(SteerType::WallAvoidance), &wallAvoid))
	{
		if (wallAvoid) Type = Type | SteerType::WallAvoidance;
		else Type = Type & (~SteerType::WallAvoidance);

	}
	if (wallAvoid)
	{
		ImGui::SliderFloat("Fleeler Length", &m_FleelerLength, 15, 100);
		ImGui::SliderFloat("Force Multi", &m_fForceMulti, 5, 100);
		ImGui::SliderFloat("Base Force", &m_fBaseForce, 30, 100);

	}
	glPushMatrix();
	glTranslatef(m_TargetPos.x, m_TargetPos.y, 0);
	glBegin(GL_LINES);
	glVertex2d(10, 10);
	glVertex2d(-10, -10);
	glVertex2d(-10, 10);
	glVertex2d(10, -10);
	glEnd();
	glPopMatrix();

	ImGui::SameLine();
	ImGui::Text(GetBehaviorName((SteerType)Type));
	/*if (Type == SteerType::Arrive)
	{
		if (ImGui::Button("Speed"))
		{
			SetArrriveType((GetArriveType() + 1) % 3);
		}
		ImGui::SameLine();
		ImGui::Text(ArriveTypeS[GetArriveType()].c_str());
	}
	
	else if (Type == SteerType::FollowPath)
	{
		ImGui::SliderFloat("m_fWayPointSeekDis", &m_fWayPointSeekDis, 5, 50);
		
	}*/

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
	else if (Type == SteerType::WallAvoidance)
	{

		glPushMatrix();
		glLoadIdentity();
		glBegin(GL_LINES);
		for (auto el : m_Fleelers)
		{
			glVertex2f(m_pOwner->GetPos().x, m_pOwner->GetPos().y);
			glVertex2f(el.x, el.y);
			
			
		}
		glEnd();
		glPopMatrix();
	}
}
bool SteeringBehavior::AccumulateForce(glm::vec2 & force, const glm::vec2 & ForcetoAdd)
{
	float CurrentForceLength = glm::length(force);
	float ForceRemain = m_pOwner->GetMaxForce() - CurrentForceLength;
	if (ForceRemain < 0.0f) return false;

	float forceLengthAdd = glm::length(ForcetoAdd);

	if (forceLengthAdd < ForceRemain)
		force += ForcetoAdd;
	else if(forceLengthAdd>0) force += glm::normalize(ForcetoAdd) * ForceRemain;
	
	return true;
}
int SteeringBehavior::IsActive(SteerType type)
{
	return type & Type;
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
	m_TargetPos = glm::vec2(0);
	m_TargetPos += v;
	if(v!=glm::vec2(0) ) m_TargetPos = glm::normalize(m_TargetPos);
	m_TargetPos *= m_fWanderRadius;
	m_TargetPos += glm::vec2(0, m_fWanderDistance);

	float angle = Vector2Angle(m_pOwner->GetVelocity()) - 90;
	
	m_TargetPos = TransfromPoint(m_TargetPos, angle, m_pOwner->GetPos());

	
	return Seek(m_TargetPos);
}

void SteeringBehavior::CreateFleeler()
{
	m_Fleelers.clear();
	glm::vec2 p;
	p = m_pOwner->GetPos() + m_FleelerLength * m_pOwner->GetFront();
	m_Fleelers.push_back(p);

	p = m_pOwner->GetPos() + m_FleelerLength * RotateVector(m_pOwner->GetFront(), 45.0f);
	m_Fleelers.push_back(p);
	p = m_pOwner->GetPos() + m_FleelerLength * RotateVector(m_pOwner->GetFront(), -45.0f);
	m_Fleelers.push_back(p);

}

glm::vec2 SteeringBehavior::WallAvoidance()
{
	auto& walls = m_pOwner->GetWorld()->GetWalls();
	CreateFleeler();

	float DistanceToCurrentIP = 0.0f,DistanceToClosestIP = 0xffffffff;
	int wallID = -1;

	glm::vec2 p, closestPoint,force;

	for (auto el : m_Fleelers)
	{
		for (int i=0; i< walls.size(); i++)
		{
if (LineIntersection(m_pOwner->GetPos(), el, walls[i].From(), walls[i].To(), p))
{
	float DistanceToCurrentIP = glm::distance(p, m_pOwner->GetPos());
	if (DistanceToCurrentIP < DistanceToClosestIP&& DistanceToCurrentIP <= m_FleelerLength + 1.0f)
	{
		DistanceToCurrentIP = DistanceToClosestIP;
		closestPoint = p;
		wallID = i;
	}
}
		}

		if (wallID >= 0)
		{
			glm::vec2 OverShoot = el - closestPoint;
			force = walls[wallID].Normal() * glm::length(OverShoot)*m_fForceMulti + walls[wallID].Normal() *m_fBaseForce;
			return (force);
		}
	}
	return Wander();
}

glm::vec2 SteeringBehavior::Interpose()
{
	GameWorld* pWorld = m_pOwner->GetWorld();
	auto& Objs = pWorld->GetObjects();

	int sz = Objs.size();
	if (sz < 2) return Wander();
	MovingObject* obj1, *obj2;
	do
	{
		obj1 = Objs[std::rand() % sz].get();
		obj2 = Objs[std::rand() % sz].get();
	} while (obj1 == obj2);


	glm::vec2 midpoint = (obj1->GetPos() + obj2->GetPos()) / 2.0f;

	float TimeToReachMidPoint = glm::distance(m_pOwner->GetPos(), midpoint) / m_pOwner->GetMaxSpeed();

	glm::vec2 aPos = obj1->GetPos() + obj1->GetVelocity() * TimeToReachMidPoint;
	glm::vec2 bPos = obj2->GetPos() + obj2->GetVelocity() * TimeToReachMidPoint;

	midpoint = (aPos + bPos) / 2.0f;

	return Arrive(midpoint, fast);
}

glm::vec2 SteeringBehavior::GetHidingPosition(const glm::vec2 & objPos, float radius, const glm::vec2 & posTarget)
{
	const float DistanceFromBoundary = 30.0f;
	float distance = DistanceFromBoundary + radius;
	glm::vec2 toObj = glm::normalize(objPos - posTarget);
	return (toObj*distance) + objPos;

}

glm::vec2 SteeringBehavior::Hide()
{
	float ClosestDistance = 0xffffffff;
	glm::vec2 BestHidingPos;
	GameWorld* pWorld = m_pOwner->GetWorld();
	auto& Objs = pWorld->GetObjects();
	auto& obstacles = pWorld->GetObstacle();

	int sz = Objs.size();
	if (sz == 1) return Wander();
	MovingObject* obj1;
	do
	{
		obj1 = Objs[std::rand() % sz].get();

	} while (obj1 == m_pOwner);


	for (auto& el : obstacles)
	{
		glm::vec2 HidePos = GetHidingPosition(el->GetPos(), el->GetRadius(), obj1->GetPos());

		float dis = glm::distance(m_pOwner->GetPos(), HidePos);

		if (dis < ClosestDistance)
		{
			ClosestDistance = dis;
			BestHidingPos = HidePos;
			//std::cout << el->GetName() << std::endl;

		}
	}

	if (ClosestDistance > 10000000.0f) return Evade(obj1);

	return Arrive(BestHidingPos, fast);
}

glm::vec2 SteeringBehavior::FollowPath()
{
	Path* pPath = m_pOwner->GetWorld()->GetPath();
	if (glm::distance(m_pOwner->GetPos(), pPath->GetCurrentWayPoint()) < m_fWayPointSeekDis)
	{
		pPath->SetNextWayPoint();
	}
	if (pPath->IsFinished()) return Arrive(pPath->GetCurrentWayPoint(), normal);

	return Seek(pPath->GetCurrentWayPoint());
}

glm::vec2 SteeringBehavior::OffsetPursut()
{
	if (m_pTarget == nullptr) return glm::vec2(0);

	glm::vec2 WorldOffsetPos = TransfromPoint(m_Offset, Vector2Angle(m_pTarget->GetVelocity()), m_pTarget->GetPos());

	glm::vec2 ToOffset = WorldOffsetPos - m_pOwner->GetPos();

	float LookAheadTime = glm::length(ToOffset) / (m_pOwner->GetMaxSpeed() + glm::length(m_pTarget->GetVelocity()));

	return Arrive(WorldOffsetPos + m_pTarget->GetVelocity()*LookAheadTime,fast);
}

glm::vec2 SteeringBehavior::Separation()
{
	glm::vec2 force(0);
	auto& objects = m_pOwner->GetWorld()->GetObjects();

	for (auto& el : objects)
	{
		if (el.get() != m_pOwner && el->IsTag())
		{
			glm::vec2 toAngent = m_pOwner->GetPos() - el->GetPos();

			force += glm::normalize(toAngent) / glm::length(toAngent);
		}
	}

	return force;
}

glm::vec2 SteeringBehavior::Alignment()
{
	glm::vec2 AvgHeading(0);
	int num = 0;
	auto& objects = m_pOwner->GetWorld()->GetObjects();

	for (auto& el : objects)
	{
		if (el.get() != m_pOwner && el->IsTag())
		{
			AvgHeading += el->GetFront();
			num++;
		}
	}

	if (num > 0)
	{
		AvgHeading /= num;
		AvgHeading -= m_pOwner->GetFront();
	}

	return AvgHeading;
}

glm::vec2 SteeringBehavior::Cohesion()
{
	glm::vec2 CenterOfMass, force(0);
	int num = 0;
	auto& objects = m_pOwner->GetWorld()->GetObjects();
	for (auto& el : objects)
	{
		if (el.get() != m_pOwner && el->IsTag())
		{
			CenterOfMass += el->GetPos();
			num++;
		}
	}

	if (num > 0)
	{
		CenterOfMass /= num;
		force = Seek(CenterOfMass);

	}

	return force;
}

glm::vec2 SteeringBehavior::Group()
{
	GameWorld* pWorld = m_pOwner->GetWorld();
	//TagNeighbors(m_pOwner, pWorld->GetObjects(), m_fViewDistance);
	auto& Objs = pWorld->GetObjects();
	for (auto obj = Objs.begin(); obj != Objs.end(); obj++)
	{
		(*obj)->UnTag();
		glm::vec2 to = (*obj)->GetPos() - m_pOwner->GetPos();
		float range = m_fViewDistance + (*obj)->GetHeight();

		if ((*obj).get() != m_pOwner && glm::length(to) < range)
			(*obj)->Tag();

	}
	glm::vec2 force = Separation() * m_fSeparationWeight;
	force += Alignment() * m_fAlignmentWeight;
	force += Cohesion() * m_fCohensionWeight;
	return force;
}

glm::vec2 SteeringBehavior::ObstacleAvoidance()
{
	TempPos = glm::vec2(0);
	GameWorld* pWorld = m_pOwner->GetWorld();
	auto& ObstacleList = pWorld->GetObstacle();
	m_fBoxLength = m_pOwner->GetHeight()*1.5f + (glm::length(m_pOwner->GetVelocity())/m_pOwner->GetMaxSpeed())*m_pOwner->GetHeight()*1.7;

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
		r = TransfromPoint(r, Vector2Angle(m_pOwner->GetVelocity())-90, m_pOwner->GetPos());
		m_TargetPos = glm::normalize(r) * m_pOwner->GetMaxSpeed();
		return Seek(r);
	}
	return Wander();
}

