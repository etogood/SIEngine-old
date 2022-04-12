#include "IndexBuffer.h"

namespace Render {
	IndexBuffer::IndexBuffer()
			: m_id_(0) {
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &m_id_);
	}

	IndexBuffer &IndexBuffer::operator=(IndexBuffer &&index_buffer) noexcept {
		m_id_ = index_buffer.m_id_;
		index_buffer.m_id_ = 0;
		return *this;
	}

	IndexBuffer::IndexBuffer(IndexBuffer &&index_buffer) noexcept:
			m_id_(index_buffer.m_id_) {
		index_buffer.m_id_ = 0;
	}

	void IndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id_);
	}

	void IndexBuffer::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::init(const void *data, const unsigned size) {
		glGenBuffers(1, &m_id_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
}