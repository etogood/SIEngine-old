#pragma once

#include <memory>
#include <string>

#include "NullObject.h"
#include "../Texture2D.h"
#include "../ShaderProgram.h"

namespace Objects {
	class Cube : public NullObject {
	public:
		Cube() = delete;

		~Cube() override = default;
		Cube(const Cube&) = delete;
		Cube& operator=(const Cube&) = delete;

		Cube(std::shared_ptr<Render::Texture2D> p_texture,
             const std::string &initial_sub_texture);

		void draw() const override;

	private:
		std::shared_ptr<Render::Texture2D> m_p_texture_2d_;

		Render::VertexBuffer m_texture_coords_buffer_;
		Render::VertexBuffer m_vertex_coords_buffer_;
        Render::VertexBuffer m_normal_vectors_buffer_;
		Render::VertexArray m_vertex_array_;
		Render::IndexBuffer m_index_buffer_;
	};
}
