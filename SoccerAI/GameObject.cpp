#include "stdafx.h"
#include "GameObject.h"

int GameObject::Counter = 0;
GameObject::GameObject(const char * name)
{
	m_iObjectID = ++Counter;
	m_Name = name;
}

int GameObject::GetID()
{
	return m_iObjectID;
}

const std::string & GameObject::GetName()
{
	return m_Name;
}
