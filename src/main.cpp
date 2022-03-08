#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "Loader/Window.h"
#include "Loader/GLLoad.h"
#include "Resources/ResourceManager.h"

glm::ivec2 default_window_size(1080, 720);

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

void main(int argc, char** argv)
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
		Resources::ResourceManager::set_executable_path(argv[0]);

		GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
		};

		auto p_default_shader_program = Resources::ResourceManager::load_shaders("DefaultShader", "res/shaders/v_shader.txt", "res/shaders/f_shader.txt");
		if (!p_default_shader_program)
		{
			std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
			return;
		}
		while (!glfwWindowShouldClose(p_window.get_window_pointer()))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 0, 3);
			/* Swap front and back buffers */
			glfwSwapBuffers(p_window.get_window_pointer());

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
}