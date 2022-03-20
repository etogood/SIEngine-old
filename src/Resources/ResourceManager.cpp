#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include "../Render/ShaderProgram.h"
#include "../Render/Sprite.h"
#include "../Render/Texture2D.h"

namespace Resources
{
	std::string ResourceManager::m_path_;
	ResourceManager::shader_programs_map ResourceManager::m_shader_programs_;
	ResourceManager::sprites_map ResourceManager::m_sprites_;
	ResourceManager::textures_2d_map ResourceManager::m_textures_2d_;

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
		m_sprites_.clear();
		m_textures_2d_.clear();
	}

	std::shared_ptr<Render::ShaderProgram> ResourceManager::get_shader_program(const std::string& shader_name)
	{
		const shader_programs_map::const_iterator it = m_shader_programs_.find(shader_name);
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
				<< std::endl;
			return nullptr;
		}
		return new_shader;
	}

	std::shared_ptr<Render::Texture2D> ResourceManager::load_texture_2d(const std::string& texture_name, const std::string& texture_path)
	{
		int channels = 0;
		int width = 0;
		int height = 0;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* pixels = stbi_load(std::string(m_path_ + "/" + texture_path).c_str(), &width, &height, &channels, STBI_rgb_alpha);

		if (!pixels)
		{
			std::cerr << "Can't load image: " << texture_path << std::endl;
			return nullptr;
		}

		std::shared_ptr<Render::Texture2D> new_texture = m_textures_2d_
			.emplace(texture_name, std::make_shared<Render::Texture2D>(width, height, pixels, GL_NEAREST, GL_CLAMP_TO_EDGE))
			.first
			->second;
		stbi_image_free(pixels);
		return new_texture;
	}

	std::shared_ptr<Render::Texture2D> ResourceManager::get_texture_2d(const std::string& texture_name)
	{
		const textures_2d_map::const_iterator it = m_textures_2d_.find(texture_name);
		if (it == m_textures_2d_.end())
		{
			std::cerr << "Can't find the texture: " << texture_name << std::endl;
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<Render::Sprite> ResourceManager::load_sprite(const std::string& sprite_name, const std::string& texture_name, const std::string& shader_name, const unsigned sprite_width, const unsigned sprite_height, const std::string& sub_texture_name)
	{
		auto p_texture = get_texture_2d(texture_name);
		if (!p_texture)
		{
			std::cerr << "Can't find the texture " << texture_name << "for the sprite " << sprite_name << std::endl;
			return nullptr;
		}
		auto p_shader = get_shader_program(shader_name);
		if (!p_shader)
		{
			std::cerr << "Can't find the shader program" << shader_name << "for the sprite " << sprite_name << std::endl;
			return nullptr;
		}
		std::shared_ptr<Render::Sprite> new_sprite = m_sprites_
			.emplace(texture_name, std::make_shared<Render::Sprite>(p_texture, sub_texture_name, p_shader, glm::vec2(0.f), glm::vec2(sprite_width, sprite_height)))
			.first
			->second;
		return new_sprite;
	}

	std::shared_ptr<Render::Sprite> ResourceManager::get_sprite(const std::string& sprite_name)
	{
		const sprites_map::const_iterator it = m_sprites_.find(sprite_name);
		if (it == m_sprites_.end())
		{
			std::cerr << "Can't find the sprite: " << sprite_name << std::endl;
			return nullptr;
		}
		return it->second;
	}
}