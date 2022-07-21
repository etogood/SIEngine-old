#pragma once

#include <memory>
#include <vector>
#include <map>
#include "ShaderProgram.h"
#include "Objects/NullObject.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

namespace Render {

	class Texture2D;

	class Scene {
	public:
        Scene() = default;

        Scene(const Scene &) = delete;

		Scene &operator=(const Scene &) = delete;

		~Scene() = default;

        static void render(GLFWwindow *p_window, Camera *camera,
                    const std::map<std::shared_ptr<Objects::NullObject>, std::tuple<std::shared_ptr<Render::ShaderProgram>>>& global_objects_map) ;
        void remove_backsides() const;
        void show_mesh();

        typedef std::tuple<std::shared_ptr<Render::ShaderProgram>> params_t;
        typedef std::map<std::shared_ptr<Objects::NullObject>, params_t> params_map_t;

    private:
        bool m_mesh_controller_ = true;
	};
}
