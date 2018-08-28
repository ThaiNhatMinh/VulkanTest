#pragma once

#define GLFW_INCLUDE_VULKAN
#include <glfw/include/GLFW/glfw3.h>

const int WIDTH = 800;
const int HEIGHT = 600;
class Application
{
public:
	void Run();

private:
	void InitWindow();
	void InitVulkan();
	void MainLoop();
	void Shutdown();
	bool checkValidationLayerSupport();
private:
	GLFWwindow * m_pWindow;
	VkInstance m_vkInstance;
};