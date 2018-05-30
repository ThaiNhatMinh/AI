#include "stdafx.h"
#include "MovingObject.h"


float fMaxSpeed = 200;
float fMaxForce = 10;
float fMaxTurnRate = 10;


MovingObject::MovingObject(const char* name):GameObject(name),m_Velocity(0),m_Front(0,1),m_Right(1,0),m_fMass(0),m_Pos(0)
{
}
