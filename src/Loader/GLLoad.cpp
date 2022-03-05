#include "GLLoad.h"

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Loader
{
	bool GLLoad::glfw_init()
	{
		if (glfwInit())
			return true;
		std::cerr << "glfwInit failed!";
		return false;
	}
	bool GLLoad::glad_init()
	{
		if (gladLoadGL())
		{
			std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;
			std::cout << "OpenGL version : " << glGetString(GL_VERSION) << std::endl;
			return true;
		}
		std::cout << "Can't load GLAD!" << std::endl;
		return false;
	}

}
