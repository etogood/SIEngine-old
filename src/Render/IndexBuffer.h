#pragma once

#include "glad/glad.h"

namespace Render {
	class IndexBuffer {
	public:
		IndexBuffer(const IndexBuffer &) = delete;

		IndexBuffer &operator=(const IndexBuffer &index_buffer) = delete;

		IndexBuffer();

		~IndexBuffer();

		IndexBuffer &operator=(IndexBuffer &&index_buffer) noexcept;

		IndexBuffer(IndexBuffer &&) noexcept;

		void init(const void *data, unsigned int size);

		void bind() const;

		static void unbind();

	private:
		GLuint m_id_;
	};
}
