#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace Render {
	ShaderProgram::ShaderProgram(const std::string &vertex_shader, const std::string &fragment_shader) {
		GLuint vertex_shader_id;
		if (!create_shader(vertex_shader, GL_VERTEX_SHADER, vertex_shader_id)) {
			std::cerr << "VERTEX SHADER compile time error!";
			return;
		}
		GLuint fragment_shader_id;
		if (!create_shader(fragment_shader, GL_FRAGMENT_SHADER, fragment_shader_id)) {
			std::cerr << "FRAGMENT SHADER compile time error!";
			glDeleteShader(vertex_shader_id);
			return;
		}
		m_id_ = glCreateProgram();
		glAttachShader(m_id_, vertex_shader_id);
		glAttachShader(m_id_, fragment_shader_id);
		glLinkProgram(m_id_);

		GLint success;
		glGetShaderiv(m_id_, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar info_log[1024];
			glGetProgramInfoLog(m_id_, 1024, nullptr, info_log);
			std::cerr << "ERROR :: SHADER LINK TIME ERROR\n" << info_log << std::endl;
		} else
			m_is_compiled_ = true;

		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);
	}

	bool ShaderProgram::is_compiled() const {
		return m_is_compiled_;
	}

	bool ShaderProgram::create_shader(const std::string &source, const GLenum shader_type, GLuint &shader_id) {
		shader_id = glCreateShader(shader_type);
		const char *code = source.c_str();
		glShaderSource(shader_id, 1, &code, nullptr);
		glCompileShader(shader_id);

		GLint success;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar info_log[1024];
			glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);
			std::cerr << "ERROR :: SHADER COMPILE TIME ERROR\n" << info_log << std::endl;
			return false;
		}
		return true;
	}

	void ShaderProgram::use() const {
		glUseProgram(m_id_);
	}

	void ShaderProgram::set_int(const std::string &name, const GLint value) const {
		glUniform1i(glGetUniformLocation(m_id_, name.c_str()), value);
	}

    void ShaderProgram::set_float(const std::string &name, GLfloat value) const {
        glUniform1f(glGetUniformLocation(m_id_, name.c_str()), value);
    }

	void ShaderProgram::set_matrix4(const std::string &name, const glm::mat4 matrix) const {
		glUniformMatrix4fv(glGetUniformLocation(m_id_, name.c_str()), 1, GL_FALSE, value_ptr(matrix));
	}

    void ShaderProgram::set_vec3(const std::string &name, glm::vec3 vector) const {
        glUniform3f(glGetUniformLocation(m_id_, name.c_str()), vector.x, vector.y, vector.z);
    }

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_id_);
	}

	ShaderProgram &ShaderProgram::operator=(ShaderProgram &&shader_program) noexcept {
		glDeleteProgram(m_id_);
		m_id_ = shader_program.m_id_;
		m_is_compiled_ = shader_program.m_is_compiled_;

		m_id_ = 0;
		m_is_compiled_ = false;
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram &&shader_program) noexcept:
			m_is_compiled_(shader_program.m_is_compiled_),
			m_id_(shader_program.m_id_) {
		shader_program.m_id_ = 0;
		shader_program.m_is_compiled_ = false;
	}


}
