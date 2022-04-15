#pragma once

#include <memory>
#include <vector>
#include "../ShaderProgram.h"
#include "NullObject.h"
#include "GLFW/glfw3.h"
#include "../Camera.h"

namespace Render {

	class Texture2D;

	class Scene {
	public:
		Scene() = delete;

		Scene(const Scene &) = delete;

		Scene &operator=(const Scene &) = delete;

		~Scene() = default;

		explicit Scene(std::shared_ptr<ShaderProgram> p_shader_program);

        void render(GLFWwindow *p_window, Camera *camera,
                    const std::vector<std::shared_ptr<Objects::NullObject>> &objects) const;

        void remove_backsides() const;
	private:
		std::shared_ptr<ShaderProgram> m_p_shader_program_;
	};
}
