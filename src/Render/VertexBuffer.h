#ifndef SIENGINE_VERTEXBUFFER_H
#define SIENGINE_VERTEXBUFFER_H

#include "glad/glad.h"

namespace Render {
	class VertexBuffer {
	public:
		VertexBuffer(const VertexBuffer &) = delete;

		VertexBuffer &operator=(const VertexBuffer &) = delete;

		VertexBuffer();

		~VertexBuffer();

		VertexBuffer(VertexBuffer &&vertex_buffer) noexcept;

		VertexBuffer &operator=(VertexBuffer &&vertex_buffer) noexcept;

		void init(const void *data, unsigned int size);

		void update(const void *data, unsigned int size) const;

		void bind() const;

		static void unbind();

	private:
		GLuint m_id_;
	};
}

#endif //SIENGINE_VERTEXBUFFER_H