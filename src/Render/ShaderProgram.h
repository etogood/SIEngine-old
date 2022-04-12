#pragma once

#include <string>
#include <glad/glad.h>

#include <glm/mat4x4.hpp>

namespace Render {
	class ShaderProgram {
	public:
		ShaderProgram() = delete;

		ShaderProgram(ShaderProgram &) = delete;

		ShaderProgram &operator=(const ShaderProgram &) = delete;

		ShaderProgram &operator=(ShaderProgram &&shader_program) noexcept;

		ShaderProgram(ShaderProgram &&shader_program) noexcept;

		ShaderProgram(const std::string &vertex_shader, const std::string &fragment_shader);

		~ShaderProgram();

		bool is_compiled() const;

		void use() const;

		void set_int(const std::string &name, GLint value) const;

		void set_matrix4(const std::string &name, glm::mat4 matrix) const;

	private:
		static bool create_shader(const std::string &source, GLenum shader_type, GLuint &shader_id);

		bool m_is_compiled_ = false;
		GLuint m_id_ = 0;
	};
}
