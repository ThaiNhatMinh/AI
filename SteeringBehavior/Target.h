#pragma once

#include "MovingObject.h"

class GameWorld;
class Target : public Vehicle
{
public:
	Target(const char* name);
	void OnCreate(GameWorld* world) {};
	void Update(float dt) {};
	void Render();
};