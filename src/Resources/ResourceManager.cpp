#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../Render/ShaderProgram.h"

namespace Resources
{
	std::string ResourceManager::m_path_;
	ResourceManager::shader_program_map ResourceManager::m_shader_programs_;

	std::string ResourceManager::get_file_string(const std::string& relative_file_path)
	{
		std::ifstream f;

		f.open(m_path_ + "/" + relative_file_path, std::ios::in | std::ios::binary);
		if (!f.is_open())
		{
			std::cerr << "Failed to open file: " << relative_file_path << std::endl;
			return std::string{};
		}
		std::stringstream buffer;
		buffer << f.rdbuf();
		return buffer.str();
	}

	void ResourceManager::set_executable_path(const std::string& executable_path)
	{
		const size_t found = executable_path.find_last_of("/\\");
		m_path_ = executable_path.substr(0, found);
	}

	void ResourceManager::unload_all_resources()
	{
		m_path_.clear();
		m_shader_programs_.clear();
	}

	std::shared_ptr<Render::ShaderProgram> ResourceManager::get_shader_program(const std::string& shader_name)
	{
		shader_program_map::const_iterator it = m_shader_programs_.find(shader_name);
		if (it == m_shader_programs_.end())
		{
			std::cerr << "Can't find shader program: " << shader_name << std::endl;
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<Render::ShaderProgram> ResourceManager::load_shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path)
	{
		std::string vertex_string = get_file_string(vertex_path);
		if (vertex_string.empty())
		{
			std::cerr << "No vertex shader!" << std::endl;
			return nullptr;
		}

		std::string fragment_string = get_file_string(fragment_path);
		if (fragment_string.empty())
		{
			std::cerr << "No fragment shader!" << std::endl;
			return nullptr;
		}

		std::shared_ptr<Render::ShaderProgram>& new_shader = m_shader_programs_.emplace(shader_name, std::make_shared<Render::ShaderProgram>(vertex_string, fragment_string)).first->second;
		if (!new_shader->is_compiled())
		{
			std::cerr
			<< "Can't load shader programs:\nVertex: "
			<< vertex_path
			<< "\nFragment: "
			<< fragment_path
			<<std::endl;
			return nullptr;
		}
		return new_shader;
	}
}
