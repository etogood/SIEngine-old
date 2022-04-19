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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
