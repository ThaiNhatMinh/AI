#include "stdafx.h"
#include "GameWorld.h"

Vehicle * GameWorld::CreateVehicle(const char * name)
{
	auto p = new Vehicle(name);
	m_ObjectList.push_back(std::unique_ptr<GameObject>(p));
	p->OnCreate(this);
	return p;
}


Target * GameWorld::CreateTarget(const char * name)
{
	auto p = new Target(name);
	m_Target = std::unique_ptr<MovingObject>(p);
	p->OnCreate(this);
	return p;
}

void GameWorld::Update(float dt)
{
	for (auto& el : m_ObjectList)
		el->Update(dt);
}

void GameWorld::Render()
{
	m_Target->Render();
	for (auto& el : m_ObjectList)
		el->Render();
}
