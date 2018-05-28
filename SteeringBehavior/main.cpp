// SteeringBehavior.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
void CursorCallBack(GLFWwindow*, double, double);
void MouseButtoncallback(GLFWwindow* window, int button, int action, int mods);
void KeyCallback(GLFWwindow*, int, int, int, int);

int Type;
Vehicle* car1 = nullptr;
Target* quad = nullptr;
int m_iWidth = 800, m_iHeight = 600;
int main()
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWmonitor* m_pMonitor = glfwGetPrimaryMonitor();

	GLFWwindow* m_pWindow = glfwCreateWindow(m_iWidth, m_iHeight, "AI", nullptr, nullptr);
	
	glfwMakeContextCurrent(m_pWindow);
	//glfwSwapInterval(1);
	glfwSetCursorPos(m_pWindow, m_iWidth / 2, m_iHeight / 2);
	glfwSetCursorPosCallback(m_pWindow, CursorCallBack);
	glfwSetMouseButtonCallback(m_pWindow, MouseButtoncallback);
	glfwSetKeyCallback(m_pWindow, KeyCallback);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "ERROR:GLEW::Init failed!\n";
		return 0;
	}
	glViewport(0,0,m_iWidth,m_iHeight);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-m_iWidth/2, m_iWidth/2, -m_iHeight/2, m_iHeight/2, -100, 100);
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glPointSize(10.0);


	GameWorld world;

	car1 = world.CreateVehicle("Car1");
	car1->SetMass(1);

	quad = world.CreateTarget("Quad");
	quad->SetPos(glm::vec2(200, 200));
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwPollEvents();
		double currentTime = glfwGetTime();
		double dt = currentTime - lastTime;
		lastTime = currentTime;


		glClearColor(0, 0.1, 0.1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		world.Update(dt);
		world.Render();
		glfwSwapBuffers(m_pWindow);
	}

	glfwTerminate();
    return 0;
}

void CursorCallBack(GLFWwindow*, double xpos, double ypos)
{
	//if (quad) quad->SetPos(glm::vec2(xpos-m_iWidth/2, m_iHeight / 2- ypos ));
}

void MouseButtoncallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		if (quad)
		{
			double xpos; double ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			quad->SetPos(glm::vec2(xpos - m_iWidth / 2, m_iHeight / 2 - ypos));
		}
	}
}

void KeyCallback(GLFWwindow*, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		Type = SteerType::Seek;
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		Type = SteerType::Flee;
}