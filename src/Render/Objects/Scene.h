#pragma once

#include <memory>
#include <vector>
#include <map>
#include "../ShaderProgram.h"
#include "NullObject.h"
#include "GLFW/glfw3.h"
#include "../Camera.h"

namespace Render {

	class Texture2D;

	class Scene {
	public:
        Scene() = default;

        Scene(const Scene &) = delete;

		Scene &operator=(const Scene &) = delete;

		~Scene() = default;

        void render(GLFWwindow *p_window, Camera *camera,
                    const std::map<std::shared_ptr<Objects::NullObject>, std::tuple<std::shared_ptr<Render::ShaderProgram>>>& global_objects_map) const;

        void remove_backsides() const;
	};
}
