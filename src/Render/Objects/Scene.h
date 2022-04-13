#pragma once

#include <memory>
#include <vector>
#include "../ShaderProgram.h"
#include "NullObject.h"
#include "GLFW/glfw3.h"

namespace Render {

	class Texture2D;

	class Scene {
	public:
		Scene() = delete;

		Scene(const Scene &) = delete;

		Scene &operator=(const Scene &) = delete;

		~Scene() = default;

		explicit Scene(std::shared_ptr<ShaderProgram> p_shader_program);

        void render(GLFWwindow *p_window, const std::vector<std::shared_ptr<Objects::NullObject>> &objects) const;

		void set_camera_x(float camera_x);

		void set_camera_y(float camera_y);

		void set_camera_z(float camera_z);

	private:
		std::shared_ptr<ShaderProgram> m_p_shader_program_;

		float m_camera_x_ = 1.f;
		float m_camera_y_ = 1.f;
		float m_camera_z_ = 1.f;
	};
}
