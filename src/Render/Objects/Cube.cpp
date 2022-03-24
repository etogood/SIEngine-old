#include "Cube.h"

namespace Objects
{
	Cube::Cube(std::shared_ptr<Render::Texture2D> p_texture,
		const std::string& initial_sub_texture,
		const glm::vec3& position,
		const glm::vec3& size, const float rotation) :
		m_p_texture_2d_(std::move(p_texture)),
		m_position_(position),
		m_size_(size),
		m_rotation_(rotation)
	{
		const auto sub_texture = m_p_texture_2d_->get_sub_texture(initial_sub_texture);

		constexpr GLfloat vertex_coords[] = {
		//	 X	  Y	   Z

			0.f, 0.f, 0.f, //near side
			0.f, 1.f, 0.f,
			1.f, 1.f, 0.f,
			1.f, 0.f, 0.f,

			0.f, 0.f, 1.f, //left side
			0.f, 1.f, 1.f,
			0.f, 1.f, 0.f,
			0.f, 0.f, 0.f,

			0.f, 0.f, 1.f, //down side
			0.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 1.f,

			1.f, 0.f, 0.f, //right side
			1.f, 1.f, 0.f,
			1.f, 1.f, 1.f,
			1.f, 0.f, 1.f,

			1.f, 0.f, 1.f, //back side
			1.f, 1.f, 1.f,
			0.f, 1.f, 1.f,
			0.f, 0.f, 1.f,

			0.f, 1.f, 0.f, //up side
			0.f, 1.f, 1.f,
			1.f, 1.f, 1.f,
			1.f, 1.f, 0.f,
		};

		const GLfloat texture_coords[] = {
			sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.right_top_uv.y,
			sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y,

			sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.right_top_uv.y,
			sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y,

			sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.right_top_uv.y,
			sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y,

			sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.right_top_uv.y,
			sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y,

			sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.right_top_uv.y,
			sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y,

			sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.right_top_uv.x, sub_texture.right_top_uv.y,
			sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y,
		};

		const GLuint indices[] = {
			0, 1, 2,
			2, 3, 0,

			0, 1, 2,
			2, 3, 0,

			0, 1, 2,
			2, 3, 0,

			0, 1, 2,
			2, 3, 0,

			0, 1, 2,
			2, 3, 0,

			0, 1, 2,
			2, 3, 0,
		};

		m_vertex_coords_buffer_.init(vertex_coords, 6 * 6 * 3 * sizeof GLfloat);
		Render::VertexBufferLayout vertex_coords_layout;
		vertex_coords_layout.add_element_layout_float(3, false);
		m_vertex_array_.add_buffer(m_vertex_coords_buffer_, vertex_coords_layout);

		m_texture_coords_buffer_.init(texture_coords, 6 * 6 * 3 * sizeof GLfloat);
		Render::VertexBufferLayout texture_coords_layout;
		texture_coords_layout.add_element_layout_float(3, false);
		m_vertex_array_.add_buffer(m_texture_coords_buffer_, texture_coords_layout);

		m_index_buffer_.init(indices, 36 * sizeof GLuint);

		Render::VertexArray::unbind();
		Render::IndexBuffer::unbind();
	}

	void Cube::set_position(const glm::vec3& position)
	{
		m_position_ = position;
	}

	void Cube::set_size(const glm::vec3& size)
	{
		m_size_ = size;
	}

	void Cube::set_rotation(const float rotation)
	{
		m_rotation_ = rotation;
	}

	void Cube::draw() const
	{
		m_vertex_array_.bind();

		glActiveTexture(GL_TEXTURE0);
		m_p_texture_2d_->bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
		Render::VertexArray::unbind();
	}
}