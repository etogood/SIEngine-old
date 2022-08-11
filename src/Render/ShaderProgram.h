#ifndef SIENGINE_SHADERPROGRAM_H
#define SIENGINE_SHADERPROGRAM_H

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

		[[nodiscard]] bool is_compiled() const;

		void use() const;

		void set_int(const std::string &name, GLint value) const;

        void set_float(const std::string &name, GLfloat value) const;

		void set_matrix4(const std::string &name, glm::mat4 matrix) const;

        void set_vec3(const std::string &name, glm::vec3 vector) const;
	private:
		static bool create_shader(const std::string &source, GLenum shader_type, GLuint &shader_id);

		bool m_is_compiled_ = false;
		GLuint m_id_ = 0;
	};
}

#endif //SIENGINE_SHADERPROGRAM_H