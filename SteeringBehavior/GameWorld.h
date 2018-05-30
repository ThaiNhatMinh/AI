#pragma once
#include <vector>
#include <memory>
class Vehicle;
class GameObject;
class Target;
class MovingObject;
class GameWorld
{

private:
	std::vector<std::unique_ptr<GameObject>> m_ObjectList;
	std::unique_ptr<MovingObject> m_Target;
public:
	GameWorld() = default;
	Vehicle * CreateVehicle(const char* name);
	void AddTarget(MovingObject* obj);
	void Update(float dt);
	void Render();
	MovingObject* GetTarget() {
		return m_Target.get();
	};
};