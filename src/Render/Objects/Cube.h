#pragma once

#include "Sprite.h"

namespace Objects
{
	class Cube
	{
	public:
		Cube() = delete;
		~Cube() = delete;
		Cube(const Cube&) = delete;
		Cube& operator=(const Cube&) = delete;

		Cube(std::shared_ptr<Render::Texture2D> p_texture,
			const std::string& initial_sub_texture,
			const glm::vec3& position = glm::vec3(0.f),
			const glm::vec3& size = glm::vec3(1.f),
			float rotation = 0.f);

		void draw() const;

		void set_position(const glm::vec3& position);
		void set_size(const glm::vec3& size);
		void set_rotation(float rotation);

	private:
		std::shared_ptr<Render::Texture2D> m_p_texture_2d_;

		glm::vec3 m_position_;
		glm::vec3 m_size_;
		float m_rotation_;

		Render::VertexBuffer m_texture_coords_buffer_;
		Render::VertexBuffer m_vertex_coords_buffer_;
		Render::VertexArray m_vertex_array_;
		Render::IndexBuffer m_index_buffer_;
	};
}
