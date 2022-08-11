//
// Created by admin on 15.04.2022.
//

#include <valarray>
#include "Sphere.h"

namespace Objects {
    Sphere::Sphere(std::shared_ptr<Render::Texture2D> p_texture, const std::string &initial_sub_texture,
                   std::shared_ptr<Render::Texture2D> p_specular_map,
                   const unsigned y_segments,
                   const unsigned x_segments) : m_p_texture_2d_(std::move(p_texture)), m_p_specular_map_(std::move(p_specular_map)),
                   m_x_segments_(x_segments), m_y_segments_(y_segments) {
		const auto sub_texture = m_p_texture_2d_->get_sub_texture(initial_sub_texture);

		for (size_t y = 0; y <= m_y_segments_; y++) {
            for (size_t x = 0; x <= m_x_segments_; x++) {
                float xSegment = (float) x / (float) m_x_segments_;
                float ySegment = (float) y / (float) m_y_segments_;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                m_vertex_coords_.push_back(xPos);
                m_vertex_coords_.push_back(yPos);
                m_vertex_coords_.push_back(zPos);

				m_texture_coords_.push_back(xSegment);
				m_texture_coords_.push_back(ySegment);
				m_texture_coords_.push_back(0);
            }
        }

        for (size_t i = 0; i <= m_y_segments_; i++) {
            for (size_t j = 0; j <= m_x_segments_; j++) {
                m_indices_.push_back(i * (x_segments + 1) + j);
                m_indices_.push_back((i + 1) * (x_segments + 1) + j);
                m_indices_.push_back((i + 1) * (x_segments + 1) + j + 1);
                m_indices_.push_back(i * (x_segments + 1) + j);
                m_indices_.push_back((i + 1) * (x_segments + 1) + j + 1);
                m_indices_.push_back(i * (x_segments + 1) + j + 1);
            }
        }

        m_vertex_coords_buffer_.init(m_vertex_coords_.data(), m_vertex_coords_.size() * sizeof(GLfloat));
        Render::VertexBufferLayout vertex_coords_layout;
        vertex_coords_layout.add_element_layout_float(3, false);
        m_vertex_array_.add_buffer(m_vertex_coords_buffer_, vertex_coords_layout);

        m_texture_coords_buffer_.init(m_texture_coords_.data(), m_texture_coords_.size() * sizeof(GLfloat));
        Render::VertexBufferLayout texture_coords_layout;
        texture_coords_layout.add_element_layout_float(3, false);
        m_vertex_array_.add_buffer(m_texture_coords_buffer_, texture_coords_layout);

        m_specular_map_coords_buffer_.init(m_texture_coords_.data(), m_texture_coords_.size() * sizeof(GLfloat));
        Render::VertexBufferLayout specular_map_coords_layout;
        specular_map_coords_layout.add_element_layout_float(3, false);
        m_vertex_array_.add_buffer(m_specular_map_coords_buffer_, specular_map_coords_layout);

        m_index_buffer_.init(m_indices_.data(), m_indices_.size() * sizeof(GLuint));

        Render::VertexArray::unbind();
        Render::IndexBuffer::unbind();
    }

    void Sphere::draw() const {
        m_vertex_array_.bind();

        glActiveTexture(GL_TEXTURE0);
        m_p_texture_2d_->bind();
        glActiveTexture(GL_TEXTURE1);
        m_p_specular_map_->bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLint>(m_indices_.size() - m_indices_.size() / m_x_segments_), GL_UNSIGNED_INT, nullptr);

        Render::VertexArray::unbind();
    }
}
