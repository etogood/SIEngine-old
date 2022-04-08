#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Loader/Window.h"
#include "Loader/GLLoad.h"
#include "Render/ShaderProgram.h"
#include "Render/Objects/Cube.h"
#include "Render/Objects/Sprite.h"
#include "Render/Objects/Scene.h"
#include "Resources/ResourceManager.h"

glm::ivec2 default_window_size(800, 600);

auto p_sprite = Resources::ResourceManager::get_sprite("default_setup");
auto p_texture = Resources::ResourceManager::get_texture_2d("default_setup");
auto p_shader_program = Resources::ResourceManager::get_shader_program("default_setup");
auto p_scene = Resources::ResourceManager::get_scene("default_setup");
auto p_cube = Resources::ResourceManager::get_cube("default_setup");

void glfw_window_size_callback(GLFWwindow* pWindow, int width, int height)
{
	default_window_size.x = width;
	default_window_size.y = height;
	glViewport(0, 0, default_window_size.x, default_window_size.y);
}

void glfw_key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
	switch (key)
	{
	case GLFW_KEY_UP:
		if (mode == GLFW_MOD_SHIFT)
		{
			p_scene->set_camera_z(-0.1f);
			break;
		}
		p_scene->set_camera_y(0.1f);
		break;
	case GLFW_KEY_DOWN:
		if (mode == GLFW_MOD_SHIFT)
		{
			p_scene->set_camera_z(0.1f);
			break;
		}
		p_scene->set_camera_y(-0.1f);
		break;
	case GLFW_KEY_LEFT:
		p_scene->set_camera_x(-0.1f);
		break;
	case GLFW_KEY_RIGHT:
		p_scene->set_camera_x(0.1f);
		break;
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

	glClearColor(0.2f, 0.2f, 1.f, 0.5f );
	{
		Resources::ResourceManager::set_executable_path(argv[0]);

		p_shader_program = Resources::ResourceManager::load_shaders("DefaultShader", "res/shaders/v_shader.txt", "res/shaders/f_shader.txt");
		if (!p_shader_program)
		{
			std::cerr << "Can't load shader program: " << "DefaultShader" << std::endl;
			return;
		}

		p_texture = Resources::ResourceManager::load_texture_2d("DefaultTexture", "res/textures_2d/container.png");
		if (!p_texture)
		{
			std::cerr << "Can't load texture: " << "DefaultTexture" << std::endl;
			return;
		}

		p_sprite = Resources::ResourceManager::load_sprite("DefaultSprite", "DefaultTexture", 16, 16);
		if (!p_sprite)
		{
			std::cerr << "Can't load sprite: " << "DefaultSprite" << std::endl;
			return;
		}

		p_scene = Resources::ResourceManager::load_scene("DefaultScene", "DefaultShader");
		if (!p_scene)
		{
			std::cerr << "Can't loat scene: " << "DefaultScene" << std::endl;
			return;
		}

		p_cube = Resources::ResourceManager::load_cube("DefaultCube", "DefaultTexture", 10, 10, 10);
		if (!p_cube)
		{
			std::cerr << "Can't load cube: " << "DefaultCube" << std::endl;
			return;
		}

		while (!glfwWindowShouldClose(p_window.get_window_pointer()))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			p_scene->render();

			//p_sprite->draw();
			p_cube->draw();
			//p_sprite->draw();

			/* Swap front and back buffers */
			glfwSwapBuffers(p_window.get_window_pointer());

			/* Poll for and process events */
			glfwPollEvents();
		}

		Resources::ResourceManager::unload_all_resources();
	}
	glfwTerminate();
}