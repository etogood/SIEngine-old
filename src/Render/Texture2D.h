#ifndef SIENGINE_TEXTURE2D_H
#define SIENGINE_TEXTURE2D_H

#include <map>
#include <string>
#include <glad/glad.h>
#include <glm/vec2.hpp>

namespace Render {
	class Texture2D {
	public:
		struct SubTexture2D {
			glm::vec2 left_bottom_uv;
			glm::vec2 right_top_uv;

			SubTexture2D(const glm::vec2 &left_bottom_uv, const glm::vec2 &right_top_uv) :
					left_bottom_uv(left_bottom_uv),
					right_top_uv(right_top_uv) {}

			SubTexture2D() :
					left_bottom_uv(0.f),
					right_top_uv(1.f) {}
		};

		Texture2D() = delete;

		Texture2D(const Texture2D &) = delete;

		Texture2D &operator=(const Texture2D &) = delete;

		Texture2D(GLuint width, GLuint height,
				  const unsigned char *data, unsigned channels = 4,
				  GLenum filter = GL_LINEAR, GLenum wrap_mode = GL_CLAMP_TO_EDGE);

		~Texture2D();

		Texture2D &operator=(Texture2D &&texture_2d) noexcept;

		Texture2D(Texture2D &&texture_2d) noexcept;

		void add_sub_texture(std::string name, const glm::vec2 &left_bottom_uv, const glm::vec2 &right_top_uv);

		const SubTexture2D &get_sub_texture(const std::string &name) const;

		unsigned width() const { return m_width_; }

		unsigned height() const { return m_height_; }

		void bind() const;

	private:
		std::map<std::string, SubTexture2D> m_sub_textures_;

		GLuint m_id_;
		GLenum m_mode_;

		unsigned m_width_;
		unsigned m_height_;
	};
}

#endif //SIENGINE_TEXTURE2D_H