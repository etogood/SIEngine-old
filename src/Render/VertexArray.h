#ifndef SIENGINE_VERTEXARRAY_H
#define SIENGINE_VERTEXARRAY_H

#include "glad/glad.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Render {
	class VertexBuffer;

	class VertexBufferLayout;

	class VertexArray {
	public:
		VertexArray(const VertexArray &) = delete;

		VertexArray &operator=(const VertexArray &) = delete;

		VertexArray();

		~VertexArray();

		VertexArray(VertexArray &&vertex_array) noexcept;

		VertexArray &operator=(VertexArray &&vertex_array) noexcept;

		void add_buffer(const VertexBuffer &vertex_buffer, const VertexBufferLayout &layout);

		void bind() const;

		static void unbind();

	private:
		GLuint m_id_ = 0;
		size_t m_elements_count_ = 0;
	};
}

#endif //SIENGINE_VERTEXARRAY_H