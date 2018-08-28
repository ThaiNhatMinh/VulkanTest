#include "stdafx.h"
#include "Application.h"

std::vector<const char*> validationLayer = { "VK_LAYER_LUNARG_standard_validation" };
#if defined(DEBUG)|| defined(_DEBUG)
const bool EnableValidationLayer = true;
#else
const bool EnableValidationLayer = false;
#endif

void Application::Run()
{
	InitWindow();
	InitVulkan();
	MainLoop();
	Shutdown();
}

void Application::InitWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	m_pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

}

void Application::InitVulkan()
{
	if (EnableValidationLayer && !checkValidationLayerSupport())
		throw std::runtime_error("validation layers requested, but not available!");


	VkApplicationInfo appinfo = {};
	appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appinfo.pApplicationName = "Hello Vulkan";
	appinfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
	appinfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appinfo.pEngineName = "Light";
	appinfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appinfo;

	uint32_t extensionCout = 0;
	const char** glfwExtension;
	glfwExtension = glfwGetRequiredInstanceExtensions(&extensionCout);

	createInfo.enabledExtensionCount = extensionCout;
	createInfo.ppEnabledExtensionNames = glfwExtension;

	if (EnableValidationLayer)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayer.size());
		createInfo.ppEnabledLayerNames = validationLayer.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}
	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS)
		throw std::runtime_error("Failed to create Vulkan instance!");

	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCout, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCout);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCout, extensions.data());

	std::cout << "Extension available: \n";
	for (auto& ext : extensions)
	{
		std::cout << "\t" << ext.extensionName << std::endl;
	}

	
}

void Application::MainLoop()
{
	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwPollEvents();
		
	}

}

void Application::Shutdown()
{
	vkDestroyInstance(m_vkInstance, nullptr);

	glfwDestroyWindow(m_pWindow);

	glfwTerminate();
}

bool Application::checkValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> availableLayer(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayer.data());
	
	for (const char* layerName : validationLayer)
	{
		bool found = false;
		for (const auto&layerProperties : availableLayer)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				found = true;
				break;
			}
		}
		if (!found) return false;
	}
}
