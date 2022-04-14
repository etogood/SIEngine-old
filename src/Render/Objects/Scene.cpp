#include "Scene.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Render {
    Scene::Scene(std::shared_ptr<ShaderProgram> p_shader_program) :
            m_p_shader_program_(move(p_shader_program)) {
    }

    void Scene::set_camera_x(const float camera_x) {
        m_camera_x_ += camera_x;
    }

    void Scene::set_camera_y(const float camera_y) {
        m_camera_y_ += camera_y;
    }

    void Scene::set_camera_z(const float camera_z) {
        m_camera_z_ += camera_z;
    }

    void Scene::render(GLFWwindow *p_window, const std::vector<std::shared_ptr<Objects::NullObject>> &objects) const {
        for (const std::shared_ptr<Objects::NullObject> &current_object: objects) {
			m_p_shader_program_->use();
            glm::mat4 model(1.f);
			model = translate(model, current_object->get_position());
			model = rotate(model, glm::radians(current_object->get_rotation().angle), current_object->get_rotation().orientation);
			model = scale(model, current_object->get_size());
			const glm::mat4 view = lookAt(glm::vec3(m_camera_x_, m_camera_y_, m_camera_z_), glm::vec3(0.5f, 0.5f, 0.5f),
                                          glm::vec3(0.f, 1.f, 0.f));
            int width, height;
            glfwGetWindowSize(p_window, &width, &height);
            const glm::mat4 projection = glm::perspective(glm::radians(90.f), (float) width / (float) height, 0.1f,
                                                          100.f);
            const glm::mat4 mvp = projection * view * model;

            m_p_shader_program_->set_int("tex", 0);
            m_p_shader_program_->set_matrix4("mvp", mvp);

			current_object->draw();
		}
    }
}