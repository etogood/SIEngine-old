#ifndef SIENGINE_RESOURCEMANAGER_H
#define SIENGINE_RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <string>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "../Render/Camera.h"
#include "../Render/ShaderProgram.h"
#include "../Render/Scene.h"
#include "../Render/Texture2D.h"
#include "../Render/Objects/Sphere.h"
#include "../Render/Objects/Model.h"
#include "../Render/Objects/Cube.h"

using namespace Objects;
using namespace Render;

namespace Resources {
    template<typename T> using map_name_ptr_t = std::map<const std::string, std::shared_ptr<T>>;
    class ResourceManager {
    public:
        ~ResourceManager() = delete;
        ResourceManager() = delete;
        ResourceManager(const ResourceManager &) = delete;
        ResourceManager &operator=(const ResourceManager &) = delete;
        ResourceManager &operator=(ResourceManager &&) = delete;
        ResourceManager(ResourceManager &&) = delete;

        static void set_executable_path(const std::string &executable_path);
        static void unload_all_resources();

        static std::shared_ptr<ShaderProgram> load_shaders(const std::string &shader_name, const std::string &vertex_path, const std::string &fragment_path);
        static std::shared_ptr<ShaderProgram> get_shader_program(const std::string &shader_name);

        static std::shared_ptr<Texture2D> load_texture_2d(const std::string &texture_name, const std::string &texture_path);
        static std::shared_ptr<Texture2D> get_texture_2d(const std::string &texture_name);

        static std::shared_ptr<Scene> load_scene(const std::string &scene_name);
        static std::shared_ptr<Scene> get_scene(const std::string &scene_name);

        static std::shared_ptr<Camera> load_camera(const std::string &camera_name, float yaw, float pitch);
        static std::shared_ptr<Camera> get_camera(const std::string &camera_name);

        static std::shared_ptr<Objects::Cube>load_cube(const std::string &cube_name, const std::string &texture_name, const std::string &specular_map_name,
                  glm::vec3 xyz = glm::vec3(1.f),
                  const std::string &sub_texture_name = "default");
        static std::shared_ptr<Cube> get_cube(const std::string &cube_name);

        static std::shared_ptr<Sphere> load_sphere(const std::string &sphere_name, const std::string &texture_name, const std::string &specular_map_name,
                    unsigned y_segments, unsigned x_segments, const std::string &sub_texture_name = "default");
        static std::shared_ptr<Sphere> get_sphere(const std::string &sphere_name);

        static std::shared_ptr<Model> load_model(const std::string& resource_name, const std::string& path);
        static std::shared_ptr<Model> get_model(const std::string& resource_name);

    private:
        static std::string m_path;

        static std::string get_file_string(const std::string &relative_file_path);

        static map_name_ptr_t<Render::Scene> m_scenes;
        static map_name_ptr_t<Render::ShaderProgram> m_shaders;
        static map_name_ptr_t<Render::Texture2D> m_textures_2d;
        static map_name_ptr_t<Render::Camera> m_cameras;

        static map_name_ptr_t<Objects::Model> m_models;
        static map_name_ptr_t<Objects::Cube> m_cubes;
        static map_name_ptr_t<Objects::Sphere> m_spheres;
    };
}

#endif //SIENGINE_RESOURCEMANAGER_H