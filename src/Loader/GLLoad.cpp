#include "GLLoad.h"

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Loader {
	bool GLLoad::glfw_init() {
		if (!glfwInit()) {
			std::cerr << "glfwInit failed!";
			return false;
		}
		return true;
	}

	bool GLLoad::glad_init() {
		if (!gladLoadGL()) {
			std::cout << "Can't load GLAD!" << std::endl;
			return false;
		}
		glEnable(GL_DEPTH_TEST);
		std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "OpenGL version : " << glGetString(GL_VERSION) << std::endl;
		return true;
	}

}
