//
// Created by admin on 15.04.2022.
//

#ifndef SIENGINE_SPHERE_H
#define SIENGINE_SPHERE_H

#include <memory>
#include "NullObject.h"
#include "../Texture2D.h"

namespace Objects {
    class Sphere : public NullObject {
    public:
        Sphere(const Sphere &) = delete;

        Sphere &operator=(const Sphere &) = delete;

        Sphere(std::shared_ptr<Render::Texture2D> p_texture,
               const std::string &initial_sub_texture,
               std::shared_ptr<Render::Texture2D> p_specular_map,
               unsigned y_segments,
               unsigned x_segments);

        void draw(std::shared_ptr<Render::ShaderProgram> shader) const override;

    private:

        unsigned m_y_segments_;
        unsigned m_x_segments_;

        std::shared_ptr<Render::Texture2D> m_p_specular_map_;
        std::shared_ptr<Render::Texture2D> m_p_texture_2d_;

        std::vector<GLfloat> m_vertex_coords_;
        std::vector<GLfloat> m_texture_coords_;
        std::vector<GLuint> m_indices_;

        Render::VertexBuffer m_texture_coords_buffer_;
        Render::VertexBuffer m_specular_map_coords_buffer_;
        Render::VertexBuffer m_vertex_coords_buffer_;
        Render::VertexArray m_vertex_array_;
        Render::IndexBuffer m_index_buffer_;
    };
}

#endif //SIENGINE_SPHERE_H
