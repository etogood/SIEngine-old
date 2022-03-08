#pragma once
#include <map>
#include <memory>
#include <string>

namespace Renderer
{
	class ShaderProgram;
}

namespace Resources
{

	class ResourceManager
	{
	public:
		~ResourceManager() = delete;
		ResourceManager() = delete;
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;
		ResourceManager(ResourceManager&&) = delete;

		static void set_executable_path(const std::string& executable_path);
		static void unload_all_resources();

		static std::shared_ptr<Renderer::ShaderProgram> load_shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);
		static std::shared_ptr<Renderer::ShaderProgram> get_shader_program(const std::string& shader_name);
	private:
		static std::string m_path_;

		static std::string get_file_string(const std::string& relative_file_path);

		typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> shader_program_map;
		static shader_program_map m_shader_programs_;
	};
}
