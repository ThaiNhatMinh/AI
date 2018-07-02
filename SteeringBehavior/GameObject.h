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
	virtual void RenderUI() = 0;
	void UnTag() { m_bTag = 0; }
	void Tag() { m_bTag = 1; }
	bool IsTag() { return m_bTag; }
private:
	int m_iObjectID;
	std::string m_Name;
	bool m_bTag = false;
	static int Counter;
};