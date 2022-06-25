#include "Scene.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Render {

    void Scene::render(GLFWwindow *p_window, Camera *camera,
                       std::map<std::shared_ptr<Objects::NullObject>, std::shared_ptr<Render::ShaderProgram>> global_objects_map) const {
        for (std::pair<const std::shared_ptr<Objects::NullObject>, std::shared_ptr<ShaderProgram>> &current_object: global_objects_map) {
            
            current_object.second->use();
            

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
            current_object.second->set_vec3("object_color", glm::vec3(1.0f, 0.5f, 0.31f));
            current_object.second->set_vec3("light_color", glm::vec3(1.0f, 1.0f, 1.0f));
            current_object.second->set_int("tex", 0);
            current_object.second->set_matrix4("mvp", mvp);

            current_object.first->draw();
        }
    }

    void Scene::remove_backsides() const {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

}