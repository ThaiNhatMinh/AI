#include "stdafx.h"
#include "GameWorld.h"

void GameWorld::CreateVehicle(MovingObject* obj)
{
	obj->OnCreate(this);
	m_ObjectList.push_back(std::unique_ptr<MovingObject>(obj));
}


void GameWorld::AddTarget(MovingObject* obj)
{
	
	m_Target = std::unique_ptr<MovingObject>(obj);
}

void GameWorld::Update(float dt)
{
	ImGui::Begin("World");
	for (auto& el : m_ObjectList)
	{
		el->Update(dt);
		if (ImGui::Button(el->GetName().c_str()))
			el->RenderUI();
	}
	ImGui::End();
}

void GameWorld::Render()
{
	//m_Target->Render();
	for (auto& el : m_ObjectList)
		el->Render();

	for (auto& el : m_ObstacleList)
		el->Render();
	for (auto& el : m_Walls)
		el.Render();

	m_Path->Render();
}

void GameWorld::Reset()
{
	for (auto& el : m_ObjectList)
		el->Reset();
}