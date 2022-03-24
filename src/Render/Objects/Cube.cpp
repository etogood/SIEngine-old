#include "Cube.h"

namespace Objects
{
	Cube::Cube(std::shared_ptr<Render::Texture2D> p_texture,
		const std::string& initial_sub_texture,
		const glm::vec3& position,
		const glm::vec3& size, float rotation) :
		m_p_texture_2d_(std::move(p_texture)),
		m_position_(position),
		m_size_(size),
		m_rotation_(rotation)
	{
		auto sub_textures = m_p_texture_2d_->get_sub_texture(initial_sub_texture);

		//constexpr GLfloat vertex_coords[] = {};
	}

	void Cube::set_position(const glm::vec3& position)
	{
		m_position_ = position;
	}

	void Cube::set_size(const glm::vec3& size)
	{
		m_size_ = size;
	}

	void Cube::set_rotation(float rotation)
	{
		m_rotation_ = rotation;
	}

	void Cube::draw() const
	{
		m_vertex_array_.bind();

		glActiveTexture(GL_TEXTURE0);
		m_p_texture_2d_->bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		Render::VertexArray::unbind();
	}
}