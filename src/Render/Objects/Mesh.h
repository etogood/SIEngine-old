//
// Created by etogood on 30.10.2022.
//

#ifndef SIENGINE_MESH_H
#define SIENGINE_MESH_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ShaderProgram.h"

#include <string>
#include <vector>
#include <memory>

#define MAX_BONE_INFLUENCE 4
namespace Objects {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        unsigned int VAO{};

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

        void draw(std::shared_ptr<Render::ShaderProgram> shader);

    private:
        unsigned int VBO{}, EBO{};

        void setupMesh();
    };
}
#endif //SIENGINE_MESH_H
