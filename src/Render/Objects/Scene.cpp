#include "Scene.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Render {
    Scene::Scene(std::shared_ptr<ShaderProgram> p_shader_program) :
            m_p_shader_program_(move(p_shader_program)) {
    }

    void Scene::render(GLFWwindow *p_window, Camera *camera,
                       const std::vector<std::shared_ptr<Objects::NullObject>> &objects) const {
        for (const std::shared_ptr<Objects::NullObject> &current_object: objects) {
            m_p_shader_program_->use();
            glm::mat4 model(1.f);
            model = translate(model, current_object->get_position());
            model = rotate(model, glm::radians(current_object->get_rotation().angle),
                           current_object->get_rotation().orientation);
            model = scale(model, current_object->get_size());
            glm::mat4 view = camera->GetViewMatrix();
            int width, height;
            glfwGetWindowSize(p_window, &width, &height);
            const glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float) width / (float) height,
                                                          0.1f,
                                                          100.f);
            const glm::mat4 mvp = projection * view * model;

            m_p_shader_program_->set_int("tex", 0);
            m_p_shader_program_->set_matrix4("mvp", mvp);

            current_object->draw();
        }
    }

    void Scene::remove_backsides() const {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
}