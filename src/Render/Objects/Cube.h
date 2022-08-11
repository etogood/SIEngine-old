#ifndef SIENGINE_CUBE_H
#define SIENGINE_CUBE_H

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
             const std::string &initial_sub_texture,
             std::shared_ptr<Render::Texture2D> p_specular_map);

		void draw() const override;

	private:
        std::shared_ptr<Render::Texture2D> m_p_texture_2d_;
        std::shared_ptr<Render::Texture2D> m_p_specular_map_;

		Render::VertexBuffer m_texture_coords_buffer_;
        Render::VertexBuffer m_specular_map_coords_buffer_;
		Render::VertexBuffer m_vertex_coords_buffer_;
		Render::VertexArray m_vertex_array_;
		Render::IndexBuffer m_index_buffer_;
	};
}

#endif //SIENGINE_CUBE_H
