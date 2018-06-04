#include "stdafx.h"
#include "GameWorld.h"

void GameWorld::CreateVehicle(MovingObject* obj)
{
	m_ObjectList.push_back(std::unique_ptr<MovingObject>(obj));
}


void GameWorld::AddTarget(MovingObject* obj)
{
	
	m_Target = std::unique_ptr<MovingObject>(obj);
}

void GameWorld::Update(float dt)
{
	for (auto& el : m_ObjectList)
		el->Update(dt);
}

void GameWorld::Render()
{
	//m_Target->Render();
	for (auto& el : m_ObjectList)
		el->Render();
}

void GameWorld::Reset()
{
	for (auto& el : m_ObjectList)
		el->Reset();
}