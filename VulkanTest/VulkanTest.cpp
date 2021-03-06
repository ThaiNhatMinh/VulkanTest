// VulkanTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/vec4.hpp>
#include <iostream>

#include "Application.h"
int main()
{
	Application app;

	try
	{
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

