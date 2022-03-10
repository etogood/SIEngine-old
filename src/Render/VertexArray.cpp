#include "VertexArray.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Render
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_id_);
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id_);
	}
	VertexArray::VertexArray(VertexArray&& vertex_array) noexcept : m_id_(vertex_array.m_id_)
	{
		vertex_array.m_id_ = 0;
	}
	VertexArray& VertexArray::operator=(VertexArray&& vertex_array) noexcept
	{
		m_id_ = vertex_array.m_id_;
		vertex_array.m_id_ = 0;
		return *this;
	}
	void VertexArray::bind() const
	{
		glBindVertexArray(m_id_);
	}
	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}
	void VertexArray::add_buffer(const VertexBuffer& vertex_buffer, const VertexBufferLayout& layout)
	{
		bind();
		vertex_buffer.bind();

		const auto& elements = layout.get_layout_elements();
		GLbyte* offset = nullptr;
		for (unsigned i = 0; i < elements.size(); ++i)
		{
			const auto& [count, type, normalized, size] = elements[i];
			const GLuint current_attribute_index = m_elements_count_ + i;
			glEnableVertexAttribArray(current_attribute_index);
			glVertexAttribPointer(current_attribute_index, size, type, normalized, layout.get_stride(), offset);
			offset += size;
		}
		m_elements_count_ += elements.size();
	}
}