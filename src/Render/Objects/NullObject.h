//
// Created by etogood on 12.04.2022.
//

#ifndef SIENGINE_NULLOBJECT_H
#define SIENGINE_NULLOBJECT_H

#include "glm/vec3.hpp"

#include "../VertexBuffer.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"

namespace Objects {
    const float PI = 3.14159265f;

    class NullObject {
    public:
        typedef struct {
            float angle;
            glm::vec3 orientation;
        } rotation_t;

        explicit NullObject(glm::vec3 m_position_ = glm::vec3(1.f),
                            glm::vec3 m_size_ = glm::vec3(1.f),
                            rotation_t m_rotation_ = {0.f, glm::vec3(1.f)});

        virtual ~NullObject() = default;

        NullObject(const NullObject &) = delete;

        NullObject &operator=(const NullObject &) = delete;

        virtual void draw() const {};

        void set_position(const glm::vec3 &position);

        void set_size(const glm::vec3 &size);

        void set_rotation(float angle, glm::vec3 orientation);


        [[nodiscard]] glm::vec3 get_position() const { return m_position_; };

		[[nodiscard]] glm::vec3 get_size() const { return m_size_; };

		[[nodiscard]] rotation_t get_rotation() const { return m_rotation_; };


	private:
		glm::vec3 m_position_;
		glm::vec3 m_size_;
		rotation_t m_rotation_;

		Render::VertexBuffer m_texture_coords_buffer_;
		Render::VertexBuffer m_vertex_coords_buffer_;
		Render::VertexArray m_vertex_array_;
	};
}
#endif //SIENGINE_NULLOBJECT_H
