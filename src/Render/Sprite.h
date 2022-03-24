#pragma once

#include <string>
#include <memory>

#include <glm/vec2.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Render
{
	class ShaderProgram;
	class Texture2D;

	class Sprite
	{
	public:
		Sprite() = delete;
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;
		virtual ~Sprite() = default;

		Sprite(std::shared_ptr<Texture2D> p_texture,
			const std::string& initial_sub_texture,
			std::shared_ptr<ShaderProgram> p_shader_program,
			const glm::vec2& position = glm::vec2(0.f),
			const glm::vec2& size = glm::vec2(1.f),
			float rotation = 0.f);

		virtual void render() const;

		void set_position(const glm::vec2& position);
		void set_size(const glm::vec2& size);
		void set_rotation(float rotation);

		void set_camera_x(float camera_x);
		void set_camera_y(float camera_y);
		void set_camera_z(float camera_z);

	private:
		std::shared_ptr<Texture2D> m_p_texture_2d_;
		std::shared_ptr<ShaderProgram> m_p_shader_program_;

		glm::vec2 m_position_;

		float m_camera_x_ = 1.f;
		float m_camera_y_ = 1.f;
		float m_camera_z_ = 1.f;

		glm::vec2 m_size_;
		float m_rotation_;

		VertexArray m_vertex_array_;
		IndexBuffer m_index_buffer_;
		VertexBuffer m_texture_coords_buffer_;
		VertexBuffer m_vertex_coords_buffer_;
	};
}
