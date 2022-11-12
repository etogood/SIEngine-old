#define GLFW_INCLUDE_NONE
#include <glm/vec2.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include "Loader/Window.h"
#include "Render/Objects/Cube.h"
#include "Render/Scene.h"
#include "Resources/ResourceManager.h"
#include "Loader/GLLoad.h"


Render::Scene::params_map_t global_objects_map;

std::string current_coords = " ";

glm::ivec2 default_window_size(1920, 1080);

glm::vec3 default_light_pos(1.2f, 1.0f, 2.0f);


float delta_time = 0.0f;
float current_time = 0.0f;


auto p_texture = Resources::ResourceManager::get_texture_2d("default_setup");
auto p_earth_texture = Resources::ResourceManager::get_texture_2d("default_setup");
auto p_container_specular_map = Resources::ResourceManager::get_texture_2d("default_setup");
auto p_shader_program = Resources::ResourceManager::get_shader_program("default_setup");
auto p_colorfill_shader_program = Resources::ResourceManager::get_shader_program("default_setup");
auto p_lightobject_shader_program = Resources::ResourceManager::get_shader_program("default_setup");
auto p_scene = Resources::ResourceManager::get_scene("default_setup");
auto p_cube = Resources::ResourceManager::get_cube("default_setup");
auto p_light_cube = Resources::ResourceManager::get_cube("default_setup");
auto p_camera = Resources::ResourceManager::get_camera("default_setup");
auto p_sphere = Resources::ResourceManager::get_sphere("default_setup");
auto p_model = Resources::ResourceManager::get_model("default_setup");


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

    p_camera->process_mouse_movement(xoffset, yoffset);
}

void glfw_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    p_camera->process_mouse_scroll(static_cast<float>(yoffset));
}

void glfw_window_size_callback(GLFWwindow *pWindow, int width, int height) {
    glViewport(0, 0, width, height);
}

void glfw_key_callback(GLFWwindow *pWindow, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
		p_scene->show_mesh();
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
        p_scene->remove_backsides();
	if (key == GLFW_KEY_W)
        p_camera->process_keyboard(Render::FORWARD, 0.002f);
    if (key == GLFW_KEY_S)
        p_camera->process_keyboard(Render::BACKWARD, 0.002f);
    if (key == GLFW_KEY_A)
        p_camera->process_keyboard(Render::LEFT, 0.002f);
    if (key == GLFW_KEY_D)
        p_camera->process_keyboard(Render::RIGHT, 0.002f);
}

void set_frame_limit(float fps) {
    static float next_time = 0.f;
    static float last_time = 0.f;
    while(glfwGetTime() < next_time) { }
    current_time = static_cast<float>(glfwGetTime());
    next_time = current_time + 1 / fps;
    delta_time = current_time - last_time;
    last_time = current_time;
}

int main(int argc, char **argv) {
	Loader::GLLoad::glfw_init();
	const auto p_window = Loader::Window(default_window_size, current_coords.c_str(), nullptr, nullptr);
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

		p_shader_program = Resources::ResourceManager::load_shaders("DefaultShader", "res/shaders/default.vert",
																	"res/shaders/default.frag");
		if (!p_shader_program) {
			std::cerr << "Can't load shader program: " << "DefaultShader" << std::endl;
			return EXIT_FAILURE;
		}

        p_colorfill_shader_program = Resources::ResourceManager::load_shaders("LightCastersShader", "res/shaders/default.vert",
                                                                    "res/shaders/default.frag");
        if (!p_colorfill_shader_program) {
            std::cerr << "Can't load shader program: " << "LightCastersShader" << std::endl;
            return EXIT_FAILURE;
        }

        p_lightobject_shader_program = Resources::ResourceManager::load_shaders("LightobjectShader", "res/shaders/default.vert",
                                                                              "res/shaders/lightobject.frag");
        if (!p_lightobject_shader_program) {
            std::cerr << "Can't load shader program: " << "LightobjectShader" << std::endl;
            return EXIT_FAILURE;
        }

		p_texture = Resources::ResourceManager::load_texture_2d("DefaultTexture", "res/textures_2d/container2.png");
		if (!p_texture) {
			std::cerr << "Can't load texture: " << "DefaultTexture" << std::endl;
			return EXIT_FAILURE;
		}

		p_earth_texture = Resources::ResourceManager::load_texture_2d("EarthTexture", "res/textures_2d/earth.jpg");
		if (!p_earth_texture) {
			std::cerr << "Can't load texture: " << "EarthTexture" << std::endl;
			return EXIT_FAILURE;
		}

        p_container_specular_map = Resources::ResourceManager::load_texture_2d("ContainerSpecularMap", "res/textures_2d/container2_specular.png");
        if (!p_container_specular_map) {
            std::cerr << "Can't load specular map: " << "ContainerSpecularMap" << std::endl;
            return EXIT_FAILURE;
        }

		p_camera = Resources::ResourceManager::load_camera("DefaultCamera", yaw, pitch);
		if (!p_camera) {
            std::cerr << "Can't load camera: " << "DefaultCamera" << std::endl;
            return EXIT_FAILURE;
        }

        p_cube = Resources::ResourceManager::load_cube("DefaultCube", "DefaultTexture", "ContainerSpecularMap");
        if (!p_cube) {
            std::cerr << "Can't load cube: " << "DefaultCube" << std::endl;
            return EXIT_FAILURE;
        }

        p_light_cube = Resources::ResourceManager::load_cube("LightCube", "DefaultTexture", "ContainerSpecularMap");
        if (!p_light_cube) {
            std::cerr << "Can't load cube: " << "LightCube" << std::endl;
            return EXIT_FAILURE;
        }

        p_sphere = Resources::ResourceManager::load_sphere("DefaultSphere", "EarthTexture", "EarthTexture", 50U, 50U);
        if (!p_sphere) {
            std::cerr << "Can't load sphere: " << "DefaultSphere" << std::endl;
            return EXIT_FAILURE;
        }

        p_model = Resources::ResourceManager::load_model("Backpack",  "res/Models/backpack/backpack.obj");
        if (!p_model) {
            std::cerr << "Can't load model: " << "Backpack" << std::endl;
            return EXIT_FAILURE;
        }

        p_scene = Resources::ResourceManager::load_scene("DefaultScene");
        if (!p_scene) {
            std::cerr << "Can't load scene: " << "DefaultScene" << std::endl;
            return EXIT_FAILURE;
        }

        //                          position

		p_cube->set_position(glm::vec3(3.2f, 3.2f, .1f));
		p_sphere->set_position(glm::vec3(-1.f, 0.f, 0.f));
		p_camera->Position = glm::vec3(1.7f, 0.8f, -5.4f);
        p_light_cube->set_position(default_light_pos);

        //                          size

		p_cube->set_size(glm::vec3(1.f, 1.f, 1.f));
        p_light_cube->set_size(glm::vec3(0.2f));

        //                          rotation

		p_cube->set_rotation(0.f, glm::vec3(1.f, 0.f, 1.f));

        //                          parameters

        Render::Scene::params_t cube_params = {p_colorfill_shader_program};
        Render::Scene::params_t model_params = {p_colorfill_shader_program};
        Render::Scene::params_t sphere_params = {p_colorfill_shader_program};
        Render::Scene::params_t lightcube_params = {p_lightobject_shader_program};

        //                           object   parameters (shader)
        //                             |            |

        global_objects_map.emplace(p_cube, cube_params);
        global_objects_map.emplace(p_model, model_params);
        global_objects_map.emplace(p_sphere, sphere_params);
        global_objects_map.emplace(p_light_cube, lightcube_params);

        while (!glfwWindowShouldClose(p_window.get_window_pointer())) {
			//current_coords = std::to_string(p_camera->Position.x) + " " + std::to_string(p_camera->Position.y) + " " + std::to_string(p_camera->Position.z);
			glfwSetWindowTitle(p_window.get_window_pointer(), ("FPS: " + std::to_string(1 / delta_time )).c_str());

			p_sphere->set_rotation(current_time, glm::vec3(0.f, 1.f, -0.3f));

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            p_scene->render(p_window.get_window_pointer(), p_camera.get(), global_objects_map);

            /* Swap front and back buffers */
            glfwSwapBuffers(p_window.get_window_pointer());

            /* Poll for and process events */
            glfwPollEvents();
            set_frame_limit(60.f);
		}
		Resources::ResourceManager::unload_all_resources();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}