#include "Texture2D.h"

namespace Render {
	Texture2D::Texture2D(const GLuint width, const GLuint height, const unsigned char *data, const unsigned channels,
						 const GLenum filter, const GLenum wrap_mode) : m_width_(width), m_height_(height) {
		switch (channels) {
			case 4:
				m_mode_ = GL_RGBA;
				break;
			case 3:
				m_mode_ = GL_RGB;
				break;
			default:
				m_mode_ = GL_RGBA;
				break;
		}

		glGenTextures(1, &m_id_);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_id_);
		glTexImage2D(GL_TEXTURE_2D, 0, m_mode_, m_width_, m_height_, 0, m_mode_, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(Texture2D &&texture_2d) noexcept: m_id_(texture_2d.m_id_), m_mode_(texture_2d.m_mode_),
														   m_width_(texture_2d.m_width_),
														   m_height_(texture_2d.m_height_) {
		texture_2d.m_id_ = 0;
	}

	Texture2D &Texture2D::operator=(Texture2D &&texture_2d) noexcept {
		glDeleteTextures(1, &m_id_);
		m_id_ = texture_2d.m_id_;
		texture_2d.m_id_ = 0;
		m_mode_ = texture_2d.m_mode_;
		m_width_ = texture_2d.m_width_;
		m_height_ = texture_2d.m_height_;
		return *this;
	}

	void Texture2D::bind() const {
		glBindTexture(GL_TEXTURE_2D, m_id_);
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_id_);
	}

	void Texture2D::add_sub_texture(std::string name, const glm::vec2 &left_bottom_uv, const glm::vec2 &right_top_uv) {
		m_sub_textures_.emplace(std::move(name), SubTexture2D(left_bottom_uv, right_top_uv));
	}

	const Texture2D::SubTexture2D &Texture2D::get_sub_texture(const std::string &name) const {
		if (const auto it = m_sub_textures_.find(name); it != m_sub_textures_.end()) {
			return it->second;
		}
		const static SubTexture2D default_sub_texture_2d;
		return default_sub_texture_2d;
	}
}