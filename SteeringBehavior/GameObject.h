#pragma once
#include <string>
class GameObject
{
public:
	GameObject(const char* name);

	int GetID();
	const std::string& GetName();
	virtual ~GameObject() = default;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
private:
	int m_iObjectID;
	std::string m_Name;
	static int Counter;
};