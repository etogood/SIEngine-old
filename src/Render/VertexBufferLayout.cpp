#include "VertexBufferLayout.h"

namespace Render
{
	VertexBufferLayout::VertexBufferLayout() : m_stride_(0)
	{
	}

	unsigned VertexBufferLayout::get_stride() const
	{
		return m_stride_;
	}

	const std::vector<VertexBufferLayoutElement>& VertexBufferLayout::get_layout_elements() const
	{
		return m_layout_elements_;
	}

	void VertexBufferLayout::reserve_elements(const size_t count)
	{
		m_layout_elements_.reserve(count);
	}

	void VertexBufferLayout::add_element_layout_float(const unsigned count, const bool normalized)
	{
		m_layout_elements_.push_back({ count, GL_FLOAT, normalized, sizeof GLfloat });
		m_stride_ += m_layout_elements_.back().size;
	}
}