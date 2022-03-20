#include "VertexBuffer.h"

namespace Render
{
	VertexBuffer::VertexBuffer() : m_id_(0)
	{
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id_);
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& vertex_buffer) noexcept : m_id_(vertex_buffer.m_id_)
	{
		vertex_buffer.m_id_ = 0;
	}

	void VertexBuffer::init(const void* data, const unsigned size)
	{
		glGenBuffers(1, &m_id_);
		glBindBuffer(GL_ARRAY_BUFFER, m_id_);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::update(const void* data, const unsigned size) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id_);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id_);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertex_buffer) noexcept
	{
		m_id_ = vertex_buffer.m_id_;
		vertex_buffer.m_id_ = 0;
		return *this;
	}
}
