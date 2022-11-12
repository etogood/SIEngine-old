#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include "../Render/ShaderProgram.h"
#include "../Render/Scene.h"
#include "../Render/Objects/Cube.h"

namespace Resources {
	std::string ResourceManager::m_path;
    Resources::map_name_ptr_t<Texture2D>    ResourceManager::m_textures_2d;
    Resources::map_name_ptr_t<ShaderProgram>    ResourceManager::m_shaders;
	Resources::map_name_ptr_t<Scene>        ResourceManager::m_scenes;
	Resources::map_name_ptr_t<Cube>         ResourceManager::m_cubes;
	Resources::map_name_ptr_t<Camera>       ResourceManager::m_cameras;
    Resources::map_name_ptr_t<Sphere>       ResourceManager::m_spheres;
    Resources::map_name_ptr_t<Model>       ResourceManager::m_models;

	std::string ResourceManager::get_file_string(const std::string &relative_file_path) {
		std::ifstream f;

		f.open(m_path + "/" + relative_file_path, std::ios::in | std::ios::binary);
		if (!f.is_open()) {
			std::cerr << "Failed to open file: " << relative_file_path << std::endl;
			return std::string{};
		}
		std::stringstream buffer;
		buffer << f.rdbuf();
		return buffer.str();
	}

	void ResourceManager::set_executable_path(const std::string &executable_path) {
        m_shaders.emplace("default_setup", nullptr);
		m_textures_2d.emplace("default_setup", nullptr);
		const size_t found = executable_path.find_last_of("/\\");
        m_path = executable_path.substr(0, found);
	}

	void ResourceManager::unload_all_resources() {
		m_path.clear();
        m_shaders.clear();
		m_textures_2d.clear();
		m_scenes.clear();
		m_cubes.clear();
	}

	std::shared_ptr<ShaderProgram> ResourceManager::get_shader_program(const std::string &shader_name) {
		if (shader_name == "default_setup") return nullptr;
		const auto it = m_shaders.find(shader_name);
		if (it == m_shaders.end()) {
			std::cerr << "Can't find shader program: " << shader_name << std::endl;
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<ShaderProgram> ResourceManager::load_shaders(const std::string &shader_name, const std::string &vertex_path,
								  const std::string &fragment_path) {
		std::string vertex_string = get_file_string(vertex_path);
		if (vertex_string.empty()) {
			std::cerr << "No vertex shader!" << std::endl;
			return nullptr;
		}

		std::string fragment_string = get_file_string(fragment_path);
		if (fragment_string.empty()) {
			std::cerr << "No fragment shader!" << std::endl;
			return nullptr;
		}

		std::shared_ptr<ShaderProgram> &new_shader = m_shaders.emplace(shader_name,
                                                                       std::make_shared<ShaderProgram>
                                                                               (vertex_string,
                                                                                fragment_string)).first->second;
		if (!new_shader->is_compiled()) {
			std::cerr
					<< "Can't load shader programs:\nVertex: "
					<< vertex_path
					<< "\nFragment: "
					<< fragment_path
					<< std::endl;
			return nullptr;
		}
		return new_shader;
	}

	std::shared_ptr<Texture2D>
	ResourceManager::load_texture_2d(const std::string &texture_name, const std::string &texture_path) {
		int channels = 0;
		int width = 0;
		int height = 0;

		stbi_set_flip_vertically_on_load(true);
		unsigned char *pixels = stbi_load(std::string(m_path + "/" + texture_path).c_str(), &width, &height, &channels,
                                          STBI_rgb_alpha);

		if (!pixels) {
			std::cerr << "Can't load image: " << texture_path << std::endl;
			return nullptr;
		}

		std::shared_ptr<Texture2D> new_texture = m_textures_2d
				.emplace(texture_name,
						 std::make_shared<Texture2D>(width, height, pixels, GL_NEAREST, GL_CLAMP_TO_EDGE))
				.first
				->second;
		stbi_image_free(pixels);
		return new_texture;
	}

	std::shared_ptr<Texture2D> ResourceManager::get_texture_2d(const std::string &texture_name) {
		if (texture_name == "default_setup") return nullptr;
		const auto it = m_textures_2d.find(texture_name);
		if (it == m_textures_2d.end()) {
			std::cerr << "Can't find the texture: " << texture_name << std::endl;
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<Scene>
	ResourceManager::load_scene(const std::string &scene_name) {
		std::shared_ptr<Scene> new_scene = m_scenes.emplace(scene_name,
                                                                    std::make_shared<Render::Scene>()).first->second;
		return new_scene;
	}

	std::shared_ptr<Scene> ResourceManager::get_scene(const std::string &scene_name) {
		if (scene_name == "default_setup") return nullptr;
		const auto it = m_scenes.find(scene_name);
		if (it == m_scenes.end()) {
			std::cerr << "Can't find the scene: " << scene_name << std::endl;
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<Cube> ResourceManager::load_cube(const std::string &cube_name,
															  const std::string &texture_name,
                                                              const std::string &specular_map_name,
															  glm::vec3 xyz,
															  const std::string &sub_texture_name) {
		auto p_texture = get_texture_2d(texture_name);
		if (!p_texture) {
			std::cerr << "Can't find the texture " << texture_name << "for the sprite " << cube_name << std::endl;
			return nullptr;
		}
        auto p_specular_map = get_texture_2d(specular_map_name);
        if (!p_specular_map){
            std::cerr << "Can't find the specular map " << texture_name << "for the sprite " << cube_name << std::endl;
            return nullptr;
        }
		std::shared_ptr<Objects::Cube> new_cube = m_cubes
				.emplace(cube_name, std::make_shared<Cube>(p_texture,  sub_texture_name, p_specular_map))
				.first
				->second;
		new_cube->set_size(glm::vec3(xyz));
		return new_cube;
	}

	std::shared_ptr<Objects::Cube> ResourceManager::get_cube(const std::string &cube_name) {
		if (cube_name == "default_setup") return nullptr;
		const auto it = m_cubes.find(cube_name);
		if (it == m_cubes.end()) {
			std::cerr << "Can't find the cube: " << cube_name << std::endl;
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<Render::Camera>
	ResourceManager::load_camera(const std::string &camera_name, float yaw, float pitch) {
		std::shared_ptr<Camera> new_camera = m_cameras
				.emplace(camera_name, std::make_shared<Camera>(yaw, pitch))
				.first
				->second;
		return new_camera;
	}

    std::shared_ptr<Camera> ResourceManager::get_camera(const std::string &camera_name) {
        if (camera_name == "default_setup") return nullptr;
        const auto it = m_cameras.find(camera_name);
        if (it == m_cameras.end()) {
            std::cerr << "Can't find the camera: " << camera_name << std::endl;
            return nullptr;
        }
        return it->second;
    }

    std::shared_ptr<Sphere> ResourceManager::load_sphere(const std::string &sphere_name, const std::string &texture_name, const std::string &specular_map_name,
                                 unsigned int y_segments, unsigned int x_segments,
                                 const std::string &sub_texture_name) {
        auto p_texture = get_texture_2d(texture_name);
        if (!p_texture) {
            std::cerr << "Can't find the texture " << texture_name << "for the sphere " << sphere_name << std::endl;
            return nullptr;
        }
        auto p_specular_map = get_texture_2d(specular_map_name);
        if (!p_specular_map) {
            std::cerr << "Can't find the specular map " << p_specular_map << "for the sphere " << sphere_name << std::endl;
            return nullptr;
        }
        std::shared_ptr<Sphere> new_sphere = m_spheres
                .emplace(sphere_name,
                         std::make_shared<Sphere>(p_texture, sub_texture_name, p_specular_map, y_segments, x_segments))
                .first
                ->second;
        return new_sphere;
    }

    std::shared_ptr<Sphere> ResourceManager::get_sphere(const std::string &sphere_name) {
        if (sphere_name == "default_setup") return nullptr;
        const auto it = m_spheres.find(sphere_name);
        if (it == m_spheres.end()) {
            std::cerr << "Can't find the sphere: " << sphere_name << std::endl;
            return nullptr;
        }
        return it->second;
    }

    std::shared_ptr<Model> ResourceManager::load_model(const std::string &resource_name, const std::string& path) {
        std::shared_ptr<Model> new_model = m_models
                .emplace(resource_name, std::make_shared<Model>(path))
                .first
                ->second;
        return new_model;
    }

    std::shared_ptr<Model> ResourceManager::get_model(const std::string &resource_name) {
        if (resource_name == "default_setup") return nullptr;
        const auto it = m_models.find(resource_name);
        if (it == m_models.end()) {
            std::cerr << "Can't find the sprite: " << resource_name << std::endl;
            return nullptr;
        }
        return it->second;
    }
}
