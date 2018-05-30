// SteeringBehavior.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
extern float fMaxSpeed;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}
glm::vec2 RandomPosOnScreen(const glm::vec2& screen, float offset);
int Type = SteerType::Seek;
int ArriveType = Deceleration::fast;
Vehicle* car1 = nullptr;
Target* quad = nullptr;
int m_iWidth = 800, m_iHeight = 600;
int CurrentKey = -1;
int main()
{
	glfwSetErrorCallback(glfw_error_callback);
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
	/*glfwSetCursorPosCallback(m_pWindow, CursorCallBack);
	glfwSetMouseButtonCallback(m_pWindow, MouseButtoncallback);
	glfwSetKeyCallback(m_pWindow, KeyCallback);*/

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

	auto quad = new Vehicle("Target");
	quad->SetPos(glm::vec2(200, 200));
	quad->SetMass(1);
	world.AddTarget(quad);
	double lastTime = glfwGetTime();


	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplGlfwGL2_Init(m_pWindow, true);

	// Setup style
	ImGui::StyleColorsDark();
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	std::vector<std::string> Behavior{ "Seek", "Flee", "Arrive","Pursuit" };
	std::vector<std::string> ArriveTypeS{ "Fast", "Normal", "Slow" };
	float totalTime = 0;
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
		if (totalTime > 2.0f)
		{
			quad->SetPos(RandomPosOnScreen(glm::vec2(m_iWidth, m_iHeight), 100));
			totalTime = 0;
		}
		world.Update(dt);
		world.Render();

		ImGui::Begin("Debug");
		ImGui::SliderFloat("Max Speed", &fMaxSpeed, 100, 400);
		
		if (ImGui::Button("Reset"))
		{
			car1->SetPos(glm::vec2(0));
			car1->SetVelocity(glm::vec2(0));
			quad->SetPos(glm::vec2(0));
			quad->SetVelocity(glm::vec2(0));
		}
		if (ImGui::Button("Behvior"))
		{
			Type = (Type + 1) % SteerType::SteerNum;
		}
		ImGui::SameLine();
		ImGui::Text(Behavior[Type].c_str());
		if (Type == SteerType::Arrive)
		{
			if (ImGui::Button("Speed"))
			{
				ArriveType = (ArriveType + 1) % 3;
			}
			ImGui::SameLine();
			ImGui::Text(ArriveTypeS[ArriveType].c_str());
		}
		ImGui::End();


		// Rendering
		/*int display_w, display_h;
		glfwGetFramebufferSize(m_pWindow, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);*/
		//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
		ImGui::Render();
		ImGui_ImplGlfwGL2_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(m_pWindow);
	}

	glfwTerminate();
    return 0;
}

glm::vec2 RandomPosOnScreen(const glm::vec2& screen, float offset)
{
	std::srand(std::time(nullptr));
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
	/*if (key == GLFW_KEY_A && action == GLFW_PRESS)
		Type = SteerType::Seek;
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		Type = SteerType::Flee;*/

	if (action == GLFW_RELEASE && key==GLFW_KEY_A)
	{
		Type = (Type + 1) % SteerType::SteerNum;
		CurrentKey = key;
		printf("Change Type: %d\n", Type);
	}
	if (action == GLFW_RELEASE && key == GLFW_KEY_S)
	{
		ArriveType = (ArriveType + 1) % 3;
		printf("Arive Change Type: %d\n", ArriveType);
	}
}