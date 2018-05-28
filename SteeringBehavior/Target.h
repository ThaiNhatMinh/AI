#pragma once

#include "MovingObject.h"

class GameWorld;
class Target : public MovingObject
{
public:
	Target(const char* name);
	void OnCreate(GameWorld* world) {};
	void Update(float dt) {};
	void Render();
};