// SteeringBehavior.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}


glm::vec2 RandomPosOnScreen(const glm::vec2& screen, float offset);

int m_iWidth = 800, m_iHeight = 600;

void WindowSizeCallback(GLFWwindow*, int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-m_iWidth / 2, m_iWidth / 2, -m_iHeight / 2, m_iHeight / 2, -100, 100);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,w, h);
}
int main()
{
	std::srand(std::time(nullptr));
	glfwSetErrorCallback(glfw_error_callback);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWmonitor* m_pMonitor = glfwGetPrimaryMonitor();

	GLFWwindow* m_pWindow = glfwCreateWindow(m_iWidth, m_iHeight, "AI", nullptr, nullptr);
	
	glfwMakeContextCurrent(m_pWindow);
	//glfwSwapInterval(1);
	glfwSetCursorPos(m_pWindow, m_iWidth / 2, m_iHeight / 2);
	/*glfwSetCursorPosCallback(m_pWindow, CursorCallBack);
	glfwSetMouseButtonCallback(m_pWindow, MouseButtoncallback);
	glfwSetKeyCallback(m_pWindow, KeyCallback);*/
	glfwSetWindowSizeCallback(m_pWindow, WindowSizeCallback);
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
	Vehicle* car1 = nullptr,*car2 = nullptr, *car3 = nullptr, *car4 = nullptr;
	//Vehicle* quad = nullptr;
	for (int i = 0; i < 40; i++)
	{
		std::string t = "Car";
		t += char('0' + i);
		car1 = new Vehicle(t.c_str());
		car1->SetMass(1);
		car1->SetSize(glm::vec2(5, 10));
		car1->GetSteerBehavior()->SetSteerType(SteerType::Group | SteerType::Wander | SteerType::ObstacleAvoidance);
		car1->SetPos(glm::vec2(std::rand()%m_iWidth, std::rand() % m_iHeight));
		world.CreateVehicle(car1);
	}
	/*quad = new Target("Target");
	quad->SetPos(glm::vec2(200, 200));
	quad->SetMass(1);*/
	
	//world.CreateVehicle(quad);

	//car1->SetTarget(car2);
	//car2->SetTarget(quad);
	world.AddObstacle(new Obstacle("Obstacle1",glm::vec2(10, 20), 75));
	world.AddObstacle(new Obstacle("Obstacle2", glm::vec2(-200, 100), 25));
	world.AddObstacle(new Obstacle("Obstacle3", glm::vec2(250, 25), 50));
	world.AddObstacle(new Obstacle("Obstacle4", glm::vec2(300, -115), 30));
	world.AddObstacle(new Obstacle("Obstacle5", glm::vec2(-290, -300), 55));
	world.AddObstacle(new Obstacle("Obstacle6", glm::vec2(-100, 250), 60));
	world.AddObstacle(new Obstacle("Obstacle7", glm::vec2(-100, -230), 40));

	int sw = m_iWidth - 100;
	int sh = m_iHeight - 100;
	world.AddWall(Wall(glm::vec2(sw / 2, sh / 2), glm::vec2(-sw / 2, sh / 2)));
	world.AddWall(Wall(glm::vec2(-sw / 2, sh / 2), glm::vec2(-sw / 2, -sh / 2)));
	world.AddWall(Wall(glm::vec2(-sw / 2, -sh / 2), glm::vec2(sw / 2, -sh / 2)));
	world.AddWall(Wall(glm::vec2(sw / 2, -sh / 2), glm::vec2(sw / 2, sh / 2)));
	double lastTime = glfwGetTime();

	Path p(5, glm::vec2(-m_iWidth / 2, -m_iHeight / 2), glm::vec2(m_iWidth / 2, m_iHeight / 2), true);
	world.SetPath(&p);
	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplGlfwGL2_Init(m_pWindow, true);

	// Setup style
	ImGui::StyleColorsDark();
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	
	float totalTime = 0;
	bool Pause = false;
	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwPollEvents();
		ImGui_ImplGlfwGL2_NewFrame();

		double currentTime = glfwGetTime();
		double dt = currentTime - lastTime;
		lastTime = currentTime;
		totalTime += dt;

		glClearColor(0, 0.1, 0.1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		if (totalTime > 1.0f)
		{
			//quad->SetPos(RandomPosOnScreen(glm::vec2(m_iWidth, m_iHeight), 50));
			totalTime = 0;
		}
		if(!Pause) world.Update(dt);
		world.Render();
		

		if (ImGui::Button("Pause")) Pause = !Pause;
		ImGui::Text("Pause: %d" ,Pause);


		ImGui::Render();
		ImGui_ImplGlfwGL2_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(m_pWindow);
	}

	glfwTerminate();
    return 0;
}

glm::vec2 RandomPosOnScreen(const glm::vec2& screen, float offset)
{
	
	int sizex = screen.x + 2 * offset;
	int sizey = screen.y + 2 * offset;
	int posx = std::rand() % sizex - sizex/2;
	int posy = std::rand() % sizey - sizey / 2;
	return glm::vec2(posx, posy);
}
void CursorCallBack(GLFWwindow*, double xpos, double ypos)
{
	//if (quad) quad->SetPos(glm::vec2(xpos-m_iWidth/2, m_iHeight / 2- ypos ));
}

void MouseButtoncallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		//if (quad)
		{
			double xpos; double ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			//quad->SetPos(glm::vec2(xpos - m_iWidth / 2, m_iHeight / 2 - ypos));
		}
	}
}

