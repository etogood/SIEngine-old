#pragma once

#include "glad/glad.h"

namespace Render
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		VertexBuffer();
		~VertexBuffer();

		VertexBuffer(VertexBuffer&& vertex_buffer) noexcept;
		VertexBuffer& operator=(VertexBuffer&& vertex_buffer) noexcept;

		void init(const void* data, const unsigned int size);
		void update(const void* data, const unsigned int size) const;

		void bind() const;
		static void unbind();
	private:
		GLuint m_id_;
	};
}
