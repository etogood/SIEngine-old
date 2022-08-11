#ifndef SIENGINE_SPRITE_H
#define SIENGINE_SPRITE_H

#include <string>
#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../Texture2D.h"

#include "NullObject.h"

namespace Objects {
    class Sprite : public NullObject {
    public:
        Sprite() = delete;

        Sprite(const Sprite &) = delete;

        Sprite &operator=(const Sprite &) = delete;

        ~Sprite() override = default;

        Sprite(std::shared_ptr<Render::Texture2D> p_texture,
			   const std::string &initial_sub_texture);

        void draw() const override;

	private:
		std::shared_ptr<Render::Texture2D> m_p_texture_2d_;

		Render::VertexArray m_vertex_array_;
		Render::IndexBuffer m_index_buffer_;
		Render::VertexBuffer m_texture_coords_buffer_;
		Render::VertexBuffer m_vertex_coords_buffer_;
	};
}

#endif //SIENGINE_SPRITE_H