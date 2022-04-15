#define GLFW_INCLUDE_NONE
#include <glm/vec2.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include "Loader/Window.h"
#include "Render/Objects/Cube.h"
#include "Render/Objects/Sprite.h"
#include "Render/Objects/Scene.h"
#include "Resources/ResourceManager.h"
#include "Loader/GLLoad.h"

glm::ivec2 default_window_size(1080, 720);

float delta_time = 0.0f;
float last_frame = 0.0f;

auto p_sprite = Resources::ResourceManager::get_sprite("default_setup");
auto p_texture = Resources::ResourceManager::get_texture_2d("default_setup");
auto p_shader_program = Resources::ResourceManager::get_shader_program("default_setup");
auto p_scene = Resources::ResourceManager::get_scene("default_setup");
auto p_cube = Resources::ResourceManager::get_cube("default_setup");
auto p_camera = Resources::ResourceManager::get_camera("default_setup");
auto p_sphere = Resources::ResourceManager::get_sphere("default_setup");

[[maybe_unused]] glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
[[maybe_unused]] glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
[[maybe_unused]] glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.f;
float pitch = 0.f;
float lastX = 800.f / 2.f;
float lastY = 600.f / 2.f;
float fov = 45.f;

void glfw_mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    p_camera->ProcessMouseMovement(xoffset, yoffset);
}

void glfw_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    p_camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void glfw_window_size_callback(GLFWwindow *pWindow, int width, int height) {
    glViewport(0, 0, width, height);
}

void glfw_key_callback(GLFWwindow *pWindow, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    if (key == GLFW_KEY_W)
        p_camera->ProcessKeyboard(Render::FORWARD, delta_time);
    if (key == GLFW_KEY_S)
        p_camera->ProcessKeyboard(Render::BACKWARD, delta_time);
    if (key == GLFW_KEY_A)
        p_camera->ProcessKeyboard(Render::LEFT, delta_time);
    if (key == GLFW_KEY_D)
        p_camera->ProcessKeyboard(Render::RIGHT, delta_time);
}

int main(int argc, char **argv) {
	Loader::GLLoad::glfw_init();
	const auto p_window = Loader::Window(default_window_size, "SIEngine", nullptr, nullptr);

	if (!p_window.init())
		return EXIT_FAILURE;
	glfwSetInputMode(p_window.get_window_pointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	p_window.set_window_size_callback(glfw_window_size_callback);
	p_window.set_key_callback(glfw_key_callback);
    p_window.set_mouse_callback(glfw_mouse_callback);
    p_window.set_scroll_callback(glfw_scroll_callback);
    p_window.make_context_current();
	Loader::GLLoad::glad_init();

	glClearColor(0.2f, 0.2f, 1.f, 0.5f);
	{
		Resources::ResourceManager::set_executable_path(argv[0]);

		p_shader_program = Resources::ResourceManager::load_shaders("DefaultShader", "res/shaders/v_shader.vs",
																	"res/shaders/f_shader.fs");
		if (!p_shader_program) {
			std::cerr << "Can't load shader program: " << "DefaultShader" << std::endl;
			return EXIT_FAILURE;
		}

		p_texture = Resources::ResourceManager::load_texture_2d("DefaultTexture", "res/textures_2d/tesak.jpg");
		if (!p_texture) {
			std::cerr << "Can't load texture: " << "DefaultTexture" << std::endl;
			return EXIT_FAILURE;
		}

		p_camera = Resources::ResourceManager::load_camera("DefaultCamera", -90.f, 0.f);
		p_sprite = Resources::ResourceManager::load_sprite("DefaultSprite", "DefaultTexture", glm::uvec2(2U));
		if (!p_sprite) {
            std::cerr << "Can't load sprite: " << "DefaultSprite" << std::endl;
            return EXIT_FAILURE;
        }

        p_cube = Resources::ResourceManager::load_cube("DefaultCube", "DefaultTexture");
        if (!p_cube) {
            std::cerr << "Can't load cube: " << "DefaultCube" << std::endl;
            return EXIT_FAILURE;
        }

        p_sphere = Resources::ResourceManager::load_sphere("DefaultSphere", "DefaultTexture", 50U, 50U);
        if (!p_sphere) {
            std::cerr << "Can't load sphere: " << "DefaultSphere" << std::endl;
            return EXIT_FAILURE;
        }

        p_scene = Resources::ResourceManager::load_scene("DefaultScene", "DefaultShader");
        if (!p_scene) {
            std::cerr << "Can't load scene: " << "DefaultScene" << std::endl;
            return EXIT_FAILURE;
        }

        std::vector<std::shared_ptr<Objects::NullObject>> objects = {
                p_cube, p_sprite, p_sphere
        };

		p_sprite->set_position(glm::vec3(3.f, 0.f, 0.f));
		p_cube->set_position(glm::vec3(0.f, 0.f, 0.f));

		p_sprite->set_size(glm::vec3(2.f, 2.f, 0.f));
		p_cube->set_size(glm::vec3(1.f, 1.f, 1.f));

		p_sprite->set_rotation(0.f, glm::vec3(1.f, 1.f, 1.f));
		p_cube->set_rotation(90.f, glm::vec3(1.f, 0.f, 1.f));

        while (!glfwWindowShouldClose(p_window.get_window_pointer())) {
            auto current_frame = static_cast<float>(glfwGetTime());
            delta_time = current_frame - last_frame;
            last_frame = current_frame;

            //glEnable(GL_CULL_FACE);
            //glCullFace(GL_BACK);

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            p_scene->render(p_window.get_window_pointer(), p_camera.get(), objects);

            /* Swap front and back buffers */
            glfwSwapBuffers(p_window.get_window_pointer());

            /* Poll for and process events */
            glfwPollEvents();
		}
		Resources::ResourceManager::unload_all_resources();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}