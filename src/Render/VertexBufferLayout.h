#ifndef SIENGINE_VERTEXBUFFERLAYOUT_H
#define SIENGINE_VERTEXBUFFERLAYOUT_H

#ifdef __GNUC__
#include <cstdlib>
#endif

#include <vector>
#include "glad/glad.h"

namespace Render {
	struct VertexBufferLayoutElement {
		GLuint count;
		GLenum type;
		GLboolean normalized;
		unsigned long long size;
	};

	class VertexBufferLayout {
	public:
		VertexBufferLayout();

		unsigned get_stride() const { return m_stride_; }

		const std::vector<VertexBufferLayoutElement> &get_layout_elements() const { return m_layout_elements_; }

		void reserve_elements(size_t count);

		void add_element_layout_float(unsigned count, bool normalized);

	private:
		std::vector<VertexBufferLayoutElement> m_layout_elements_;
		unsigned m_stride_;
	};
}

#endif //SIENGINE_VERTEXBUFFERLAYOUT_H
