#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream>

#include "Loader/Window.h"
#include "Loader/GLLoad.h"

glm::ivec2 default_window_size(640, 480);

void glfw_window_size_callback(GLFWwindow* pWindow, int width, int height)
{
	default_window_size.x = width;
	default_window_size.y = height;
	glViewport(0, 0, default_window_size.x, default_window_size.y);
}

void glfw_key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
}

void main()
{
	Loader::GLLoad::glfw_init();
	const auto p_window = Loader::Window(default_window_size, "SIEngine", nullptr, nullptr);
	
	if (!p_window.init())
		return;
	p_window.set_window_size_call_back(glfw_window_size_callback);
	p_window.set_key_call_back(glfw_key_callback);
	p_window.make_context_current();
	Loader::GLLoad::glad_init();

	glClearColor(1, 0, 1, 0);
	{
		while (!glfwWindowShouldClose(p_window.get_window_pointer()))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(p_window.get_window_pointer());

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
}