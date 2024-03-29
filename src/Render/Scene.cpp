#include "Scene.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Render {

    void Scene::render(GLFWwindow *p_window, Camera *camera,
                       const std::map<std::shared_ptr<Objects::NullObject>, std::tuple<std::shared_ptr<Render::ShaderProgram>>> &global_objects_map) {
        for (std::pair<const std::shared_ptr<Objects::NullObject>, std::tuple<std::shared_ptr<Render::ShaderProgram>>> current_object: global_objects_map) {
            auto shader_program = std::get<0>(current_object.second);
            shader_program->use();

            glm::mat4 model(1.f);
            model = translate(model, current_object.first->get_position());
            model = rotate(model, glm::radians(current_object.first->get_rotation().angle),
                           current_object.first->get_rotation().orientation);
            model = scale(model, current_object.first->get_size());
            glm::mat4 view = camera->GetViewMatrix();
            int width, height;
            glfwGetWindowSize(p_window, &width, &height);
            const glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float) width / (float) height,
                                                          0.1f,
                                                          100.f);
            const glm::mat4 mvp = projection * view * model;

            shader_program->set_vec3("view_pos", camera->Position);
            shader_program->set_vec3("light.position", glm::vec3(1.2f, 1.f, 2.f));

            shader_program->set_vec3("light.diffuse", glm::vec3(.5f, .5f, .5f));
            shader_program->set_vec3("light.ambient", glm::vec3(.3f, .3f, .3f));
            shader_program->set_vec3("light.specular", glm::vec3(1.f, 1.f, 1.f));

            shader_program->set_int("material.diffuse", 0);
            shader_program->set_int("material.specular", 1);
            shader_program->set_float("material.shininess", 32.f);

            shader_program->set_float("light.constant", 1.f);
            shader_program->set_float("light.linear", 0.09f);
            shader_program->set_float("light.quadratic", 0.032f);

            shader_program->set_matrix4("model", model);
            shader_program->set_matrix4("mvp", mvp);

            current_object.first->draw();
        }
    }

    void Scene::remove_backsides() const {
        if (glIsEnabled(GL_CULL_FACE)){
            glDisable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            return;
        }
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    void Scene::show_mesh() {
        if (m_mesh_controller_){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            m_mesh_controller_ = false;
            return;
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_mesh_controller_ = true;
    }
}