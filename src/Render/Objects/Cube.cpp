#include "Cube.h"

#include <utility>


namespace Objects {
    Cube::Cube(std::shared_ptr<Render::Texture2D> p_texture,
               const std::string &initial_sub_texture,
               std::shared_ptr<Render::Texture2D> p_specular_map) :
            m_p_texture_2d_(std::move(p_texture)),
            m_p_specular_map_(std::move(p_specular_map)){

		constexpr GLfloat vertex_coords[] = {
				//	 X	  Y	   Z

				0.f, 0.f, 0.f,     //near side
				0.f, 1.f, 0.f,
				1.f, 1.f, 0.f,
				1.f, 0.f, 0.f,

				1.f, 0.f, 0.f, //right side
				1.f, 1.f, 0.f,
				1.f, 1.f, 1.f,
				1.f, 0.f, 1.f,

				1.f, 1.f, 0.f, //top side
				0.f, 1.f, 0.f,
				0.f, 1.f, 1.f,
				1.f, 1.f, 1.f,

				0.f, 0.f, 1.f,  //left side
				0.f, 1.f, 1.f,
				0.f, 1.f, 0.f,
				0.f, 0.f, 0.f,

				1.f, 0.f, 1.f, //back side
				1.f, 1.f, 1.f,
				0.f, 1.f, 1.f,
				0.f, 0.f, 1.f,

				0.f, 0.f, 1.f,  //bottom side
				0.f, 0.f, 0.f,
				1.f, 0.f, 0.f,
				1.f, 0.f, 1.f
		};

		const auto sub_texture = m_p_texture_2d_->get_sub_texture(initial_sub_texture);

		const GLfloat texture_coords[] = {
				sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y, 0,
				sub_texture.right_top_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y, 0,

				sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y, 0,
				sub_texture.right_top_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y, 0,

				sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y, 0,
				sub_texture.right_top_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y, 0,

				sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y, 0,
				sub_texture.right_top_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y, 0,

				sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y, 0,
				sub_texture.right_top_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y, 0,

				sub_texture.right_top_uv.x, sub_texture.left_bottom_uv.y, 0,
				sub_texture.right_top_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.right_top_uv.y, 0,
				sub_texture.left_bottom_uv.x, sub_texture.left_bottom_uv.y, 0,

		};

		constexpr GLuint indices[] = {
				0U, 1U, 2U,
				2U, 3U, 0U,

				4U, 5U, 6U,
				6U, 7U, 4U,

				8U, 9U, 10U,
				10U, 11U, 8U,

				12U, 13U, 14U,
				14U, 15U, 12U,

				16U, 17U, 18U,
				18U, 19U, 16U,

				20U, 21U, 22U,
				22U, 23U, 20U
		};

		m_vertex_coords_buffer_.init(vertex_coords, 3 * 6 * 6 * 6 * sizeof(GLfloat));
		Render::VertexBufferLayout vertex_coords_layout;
		vertex_coords_layout.add_element_layout_float(3, false);
		m_vertex_array_.add_buffer(m_vertex_coords_buffer_, vertex_coords_layout);

		m_texture_coords_buffer_.init(texture_coords, 3 * 6 * 6 * 6 * sizeof(GLfloat));
		Render::VertexBufferLayout texture_coords_layout;
		texture_coords_layout.add_element_layout_float(3, false);
		m_vertex_array_.add_buffer(m_texture_coords_buffer_, texture_coords_layout);

        m_specular_map_coords_buffer_.init(texture_coords, 3 * 6 * 6 * 6 * sizeof(GLfloat));
        Render::VertexBufferLayout specular_map_coords_layout;
        specular_map_coords_layout.add_element_layout_float(3, false);
        m_vertex_array_.add_buffer(m_specular_map_coords_buffer_, specular_map_coords_layout);

		m_index_buffer_.init(indices, 36 * sizeof(GLuint));

		Render::VertexArray::unbind();
		Render::IndexBuffer::unbind();
	}

	void Cube::draw(std::shared_ptr<Render::ShaderProgram> shader) const {
        m_vertex_array_.bind();

        glActiveTexture(GL_TEXTURE0);
        m_p_texture_2d_->bind();
        glActiveTexture(GL_TEXTURE1);
        m_p_specular_map_->bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        Render::VertexArray::unbind();
    }
}