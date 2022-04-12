#pragma once

#include <map>
#include <memory>
#include <string>

namespace Render {
	class Scene;

	class Texture2D;

	class ShaderProgram;
}

namespace Objects {
	class Sprite;

	class Cube;
}

namespace Resources {

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

		static std::shared_ptr<Render::ShaderProgram>
		load_shaders(const std::string &shader_name, const std::string &vertex_path, const std::string &fragment_path);

		static std::shared_ptr<Render::ShaderProgram> get_shader_program(const std::string &shader_name);

		static std::shared_ptr<Render::Texture2D>
		load_texture_2d(const std::string &texture_name, const std::string &texture_path);

		static std::shared_ptr<Render::Texture2D> get_texture_2d(const std::string &texture_name);

		static std::shared_ptr<Render::Scene> load_scene(const std::string &scene_name, const std::string &shader_name);

		static std::shared_ptr<Render::Scene> get_scene(const std::string &scene_name);

		static std::shared_ptr<Objects::Cube>
		load_cube(const std::string &cube_name, const std::string &texture_name, const std::string &shader_program_name,
				  unsigned cube_width,
				  unsigned cube_height, unsigned cube_length,
				  const std::string &sub_texture_name = "default");

		static std::shared_ptr<Objects::Cube> get_cube(const std::string &cube_name);

		static std::shared_ptr<Objects::Sprite>
		load_sprite(const std::string &sprite_name, const std::string &texture_name, unsigned sprite_width,
					unsigned sprite_height, const std::string &sub_texture_name = "default");

		static std::shared_ptr<Objects::Sprite> get_sprite(const std::string &sprite_name);

	private:
		static std::string m_path_;

		static std::string get_file_string(const std::string &relative_file_path);

		typedef std::map<const std::string, std::shared_ptr<Render::Scene>> scenes_map;
		static scenes_map m_scenes_;

		typedef std::map<const std::string, std::shared_ptr<Render::ShaderProgram>> shader_programs_map;
		static shader_programs_map m_shader_programs_;

		typedef std::map<const std::string, std::shared_ptr<Render::Texture2D>> textures_2d_map;
		static textures_2d_map m_textures_2d_;

		typedef std::map<const std::string, std::shared_ptr<Objects::Sprite>> sprites_map;
		static sprites_map m_sprites_;

		typedef std::map<const std::string, std::shared_ptr<Objects::Cube>> cubes_map;
		static cubes_map m_cubes_;
	};
}