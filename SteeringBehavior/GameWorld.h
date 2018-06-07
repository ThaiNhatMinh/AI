#pragma once
#include <vector>
#include <memory>
class Vehicle;
class Target;
class MovingObject;
class GameWorld
{

private:
	std::vector<std::unique_ptr<MovingObject>> m_ObjectList;
	std::unique_ptr<MovingObject> m_Target;
	std::vector<std::unique_ptr<Obstacle>> m_ObstacleList;
public:
	GameWorld() = default;
	void CreateVehicle(MovingObject* obj);
	void AddTarget(MovingObject* obj);
	void Update(float dt);
	void Reset();
	void Render();
	MovingObject* GetTarget() {
		return m_Target.get();
	};

	void AddObstacle(Obstacle* obs) {
		m_ObstacleList.push_back(std::unique_ptr<Obstacle>(obs));
	};
	const std::vector<std::unique_ptr<Obstacle>>& GetObstacle() { return m_ObstacleList; }
};