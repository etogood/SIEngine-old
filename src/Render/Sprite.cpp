#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "VertexBufferLayout.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/glfw3.h"

namespace Render
{
	Sprite::Sprite(std::shared_ptr<Texture2D> p_texture,
		const std::string& initial_sub_texture,
		std::shared_ptr<ShaderProgram> p_shader_program,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation) :
		m_p_texture_2d_(std::move(p_texture)),
		m_p_shader_program_(std::move(p_shader_program)),
		m_position_(position),
		m_size_(size),
		m_rotation_(rotation)
	{
		auto& sub_texture = m_p_texture_2d_->get_sub_texture(initial_sub_texture);

		constexpr GLfloat vertex_coords[] =
		{
		//	 X	  Y

			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
		};

		const GLfloat texture_coords[] =
		{
			sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y,
			sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y,

			sub_texture.right_top_uv.x, sub_texture.right_top_uv.y,
			sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y
		};

		const GLuint indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		m_vertex_coords_buffer_.init(vertex_coords, 4 * 2 * sizeof GLfloat);
		VertexBufferLayout vertex_coords_layout;
		vertex_coords_layout.add_element_layout_float(2, false);
		m_vertex_array_.add_buffer(m_vertex_coords_buffer_, vertex_coords_layout);

		m_texture_coords_buffer_.init(texture_coords, 4 * 2 * sizeof GLfloat);
		VertexBufferLayout texture_coords_layout;
		texture_coords_layout.add_element_layout_float(2, false);
		m_vertex_array_.add_buffer(m_texture_coords_buffer_, texture_coords_layout);

		m_index_buffer_.init(indices, 2 * 3 * sizeof GLuint);

		VertexArray::unbind();
		IndexBuffer::unbind();
	}

	void Sprite::set_position(const glm::vec2& position)
	{
		m_position_ = position;
	}

	void Sprite::set_rotation(const float rotation)
	{
		m_rotation_ = rotation;
	}

	void Sprite::set_size(const glm::vec2& size)
	{
		m_size_ = size;
	}

	void Sprite::render() const
	{
		m_p_shader_program_->use();

		glm::mat4 model(1.f);

		model = translate(model, glm::vec3(m_position_, 0.f));
		model = translate(model, glm::vec3(0.5f * m_size_.x, 0.5f * m_size_.y, 0.f));
		model = rotate(model, glm::radians(m_rotation_), glm::vec3(1.f, 0.f, 0.f));
		//model = translate(model, glm::vec3(-0.5f * m_size_.x, -0.5f * m_size_.y, 0.f));
		model = scale(model, glm::vec3(m_size_, 1.f));
		
		model = rotate(model, glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f));

		glm::mat4 view(1.f);
		view = translate(view, glm::vec3(0.f, 0.f, -3.f));

		glm::mat4 projection = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f);


		m_vertex_array_.bind();

		m_p_shader_program_->set_matrix4("modelMat", model);
		m_p_shader_program_->set_matrix4("viewMat", view);
		m_p_shader_program_->set_matrix4("projectionMat", projection);

		glActiveTexture(GL_TEXTURE0);
		m_p_texture_2d_->bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		VertexArray::unbind();
	}
}
