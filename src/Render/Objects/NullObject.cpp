//
// Created by etogood on 12.04.2022.
//

#include "NullObject.h"

namespace Objects {

	NullObject::NullObject(glm::vec3 position, glm::vec3 size, float rotation) : m_position_(position),
																				 m_rotation_(rotation),
																				 m_size_(size) {
	}

	void NullObject::set_position(const glm::vec3 &position) {
		m_position_ = position;
	}

	void NullObject::set_size(const glm::vec3 &size) {
		m_size_ = size;
	}

	void NullObject::set_rotation(float rotation) {
		m_rotation_ = rotation;
	}
}
