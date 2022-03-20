#include "VertexBufferLayout.h"

namespace Render
{
	VertexBufferLayout::VertexBufferLayout() : m_stride_(0)
	{
	}

	void VertexBufferLayout::reserve_elements(const size_t count)
	{
		m_layout_elements_.reserve(count);
	}

	void VertexBufferLayout::add_element_layout_float(const unsigned count, const bool normalized)
	{
		m_layout_elements_.push_back({ count, GL_FLOAT, normalized, count * sizeof GLfloat });
		m_stride_ += m_layout_elements_.back().size;
	}
}