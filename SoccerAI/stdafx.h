// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <ctime>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\geometric.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\mat2x2.hpp>
#include <glm/geometric.hpp>


// TODO: reference additional headers your program requires here
#include "Telegram.h"

#include "Wall.h"
#include "GameObject.h"
#include "MovingObject.h"
#include "SoccerPitch.h"