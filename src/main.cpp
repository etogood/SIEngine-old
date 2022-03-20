#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Loader/Window.h"
#include "Loader/GLLoad.h"
#include "Render/ShaderProgram.h"
#include "Render/Sprite.h"
#include "Render/Texture2D.h"
#include "Resources/ResourceManager.h"

glm::ivec2 default_window_size(800, 600);

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

	glClearColor(0.2f, 0.2f, 1.f, 0.5f);
	{
		Resources::ResourceManager::set_executable_path(argv[0]);

		const auto p_default_shader_program = Resources::ResourceManager::load_shaders("DefaultShader", "res/shaders/v_shader.txt", "res/shaders/f_shader.txt");
		if (!p_default_shader_program)
		{
			std::cerr << "Can't load shader program: " << "DefaultShader" << std::endl;
			return;
		}

		const auto p_texture = Resources::ResourceManager::load_texture_2d("DefaultTexture", "res/textures_2d/container.png");
		if (!p_texture)
		{
			std::cerr << "Can't load texture: " << "DefaultTexture" << std::endl;
			return;
		}

		const auto p_sprite = Resources::ResourceManager::load_sprite("DefaultSprite", "DefaultTexture", "DefaultShader", 16, 16);
		if (!p_sprite)
		{
			std::cerr << "Can't load sprite program: " << "DefaultSprite" << std::endl;
			return;
		}
		p_sprite->set_position(glm::vec2(100));
		p_sprite->set_size(glm::vec2(400));

		const glm::mat4 projection_matrix = glm::ortho(0.f, static_cast<float>(p_window.width()), 0.f, static_cast<float>(p_window.height()), -100.f, 100.f);

		p_default_shader_program->use();
		p_default_shader_program->set_int("tex", 0);
		p_default_shader_program->set_matrix4("projectionMat", projection_matrix);










		
		while (!glfwWindowShouldClose(p_window.get_window_pointer()))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			p_sprite->render();
			/* Swap front and back buffers */
			glfwSwapBuffers(p_window.get_window_pointer());

			/* Poll for and process events */
			glfwPollEvents();
		}
		Resources::ResourceManager::unload_all_resources();
	}
	glfwTerminate();
}