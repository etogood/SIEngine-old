//
// Created by etogood on 14.04.2022.
//

#ifndef SIENGINE_CAMERA_H
#define SIENGINE_CAMERA_H

#include "glm/vec3.hpp"
#include "glm/ext/matrix_float4x4.hpp"

namespace Render {
	enum CameraMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	const float YAW = -90.0f;
	const float PITCH = 0.0f;
    const float SPEED = 100.f;
    const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	class Camera {
	public:
		Camera(const Camera &) = delete;

		Camera &operator=(const Camera &) = delete;

		explicit Camera(float yaw = YAW, float pitch = PITCH, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW,
			   float pitch = PITCH);

		Camera(glm::vec3 position, float upX, float upY, float upZ, float yaw = YAW, float pitch = PITCH);

		Camera(float posX, float posY, float posZ, glm::vec3 up, float yaw = YAW, float pitch = PITCH);

		// camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		// euler Angles
		float Yaw;
		float Pitch;

		// camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

        [[nodiscard]] glm::mat4 get_view_matrix() const;

		void process_keyboard(CameraMovement direction, float deltaTime);

        void process_mouse_movement(float xoffset, float yoffset, bool constrainPitch = true);

		void process_mouse_scroll(float yoffset);
	private:
		void update_camera_vectors();
	};
}
#endif //SIENGINE_CAMERA_H