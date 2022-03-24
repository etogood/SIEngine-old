#pragma once

#include <memory>

namespace Render
{
	class ShaderProgram;
	class Texture2D;

	class Scene
	{
	public:
		Scene() = delete;
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		virtual ~Scene() = default;

		Scene(std::shared_ptr<ShaderProgram> p_shader_program);

		virtual void render() const;

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
