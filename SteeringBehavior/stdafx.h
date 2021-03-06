// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <math.h>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\geometric.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\mat2x2.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <glm/geometric.hpp>

#include "Ultil.h"
#include "Path.h"
#include "Vehicle.h"
#include "Target.h"
#include "Obstacle.h"
#include "Wall.h"
#include "GameWorld.h"

#include "imgui.h"
#include "imgui_impl_glfw_gl2.h"
// TODO: reference additional headers your program requires here
